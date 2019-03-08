/** @file
 * Respacker to make resource embedded.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <miniz/miniz.h>
#include <cxxopts/cxxopts.hpp>
using namespace std;

const char* kFileCmd = "files";
unsigned char kResID[] = {0x55, 0x49};  // Identifier "UI"

shared_ptr<unsigned char> ReadFile(string filename, long* size);
bool WriteFile(string filename, const void* buffer, long size);

template <typename T>
shared_ptr<T> make_shared_array(size_t size) {
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}

int main(int argc, char* argv[]) {
    try {
        bool opt_unpack = false, opt_nobackup = false;
        string exepath, zippath;

        cxxopts::Options options(argv[0], "ResPacker CLI options");
        options.positional_help("[exefile] [zipfile]").show_positional_help();

        // clang-format off
        options.add_options()("h,help", "Print help")
                             ("nobackup", "Do not make backup file",
                              cxxopts::value<bool>(opt_nobackup))
                             ("u,unpack", "Unpack mode",
                              cxxopts::value<bool>(opt_unpack))
                             (kFileCmd,"exe and zip file path",
                              cxxopts::value<vector<string>>());
        // clang-format on
        options.parse_positional(kFileCmd);

        auto result = options.parse(argc, argv);

        // help
        if (result.count("h")) {
            cout << options.help();
            return 0;
        }

        // error detect
        switch (result.count(kFileCmd)) {
            case 0:
                cout << "exefile is needed." << endl;
                return 1;
            case 1:
                if (!opt_unpack) {
                    cout << "zipfile is needed." << endl;
                    return 1;
                }
                exepath = result[kFileCmd].as<vector<string>>()[0];
                break;
            case 2:
                if (opt_unpack) {
                    cout << "Unknown argument "
                         << result[kFileCmd].as<vector<string>>()[1] << endl;
                    return 1;
                }
                exepath = result[kFileCmd].as<vector<string>>()[0];
                zippath = result[kFileCmd].as<vector<string>>()[1];
                break;
            default:
                cout << "Too many arguments!" << endl;
                return 1;
        }

        // working
        long zipsize, exesize;

        if (opt_unpack) {
            // reading packed exefile
            cout << "Reading " << exepath << endl;
            auto fp =
                shared_ptr<FILE>(fopen(exepath.c_str(), "rb"), [](FILE* fp) {
                    if (fp)
                        fclose(fp);
                });
            if (!fp) {
                cout << exepath << " can't access!" << endl;
                return 1;
            }

            // reading original exefile
            fseek(fp.get(), -(long)sizeof(exesize), SEEK_END);
            if (fread(&exesize, sizeof(exesize), 1, fp.get()) != 1) {
                cout << "Reading filesize error!" << endl;
                return 1;
            }
            fseek(fp.get(), 0, SEEK_SET);
            auto exefile = make_shared_array<unsigned char>(exesize);
            if (fread(exefile.get(), exesize, 1, fp.get()) != 1) {
                cout << "Reading " << exepath << " error!" << endl;
                return 1;
            }

            unsigned char fileid[2];
            // varify id
            if (fread(fileid, 2, 1, fp.get()) != 1) {
                cout << "Reading identifier error!" << endl;
                return 1;
            }
            if (fileid[0] != kResID[0] ||
                fileid[1] != kResID[1]) {  // not packed exe
                cout << "Varify error! Perhaps not UI packed exefile." << endl;
                return 1;
            }

            // reading zipfile
            if (fread(&zipsize, sizeof(zipsize), 1, fp.get()) != 1) {
                cout << "Reading filesize error!" << endl;
                return 1;
            }
            auto zipfile = make_shared_array<unsigned char>(zipsize);
            if (fread(zipfile.get(), zipsize, 1, fp.get()) != 1) {
                cout << "Reading " << zippath << " error!" << endl;
                return 1;
            }

            // seperate files
            if (!WriteFile(exepath + ".src", exefile.get(), exesize))
                return 1;
            if (!WriteFile(exepath + ".zip", zipfile.get(), zipsize))
                return 1;
        } else {
            // reading zip and exe file
            auto zipfile = ReadFile(zippath, &zipsize);
            if (!zipfile)
                return 1;

            auto exefile = ReadFile(exepath, &exesize);
            if (!exefile)
                return 1;

            // make bakfile
            if (!opt_nobackup)
                if (!WriteFile(exepath + ".bak", exefile.get(), exesize))
                    return 1;

            // append exefile
            cout << "Appending to " << exepath << " ..." << endl;
            auto fp =
                shared_ptr<FILE>(fopen(exepath.c_str(), "ab"), [](FILE* fp) {
                    if (fp)
                        fclose(fp);
                });
            if (!fp) {
                cout << exepath << " can't access!" << endl;
                return 1;
            }
            if (fwrite(kResID, 2, 1, fp.get()) != 1 ||
                fwrite(&zipsize, sizeof(zipsize), 1, fp.get()) != 1 ||
                fwrite(zipfile.get(), zipsize, 1, fp.get()) != 1 ||
                fwrite(&exesize, sizeof(exesize), 1, fp.get()) != 1) {
                cout << "Writting to " << exepath << " failed!" << endl;
                return 1;
            }
        }
        cout << "Process successfully!" << endl;
    } catch (const cxxopts::OptionException& e) {
        cout << "Error parsing options: " << e.what() << endl;
        return 1;
    }
    return 0;
}

shared_ptr<unsigned char> ReadFile(string filename, long* size) {
    cout << "Reading " << filename << " ..." << endl;
    auto fp = shared_ptr<FILE>(fopen(filename.c_str(), "rb"), [](FILE* fp) {
        if (fp)
            fclose(fp);
    });
    if (!fp) {
        cout << filename << " can't access!" << endl;
        return nullptr;
    }
    fseek(fp.get(), 0, SEEK_END);
    *size = ftell(fp.get());
    rewind(fp.get());
    auto file = make_shared_array<unsigned char>(*size);
    if (fread(file.get(), *size, 1, fp.get()) != 1) {
        cout << "Reading " << filename << " error!" << endl;
        return nullptr;
    }
    return file;
}

bool WriteFile(string filename, const void* buffer, long size) {
    cout << "Writting to " << filename << " ..." << endl;
    auto fp = shared_ptr<FILE>(fopen(filename.c_str(), "wb"), [](FILE* fp) {
        if (fp)
            fclose(fp);
    });
    if (!fp) {
        cout << filename << " can't access!" << endl;
        return nullptr;
    }

    if (fwrite(buffer, size, 1, fp.get()) != 1) {
        cout << "Writting to " << filename << " failed!" << endl;
        return false;
    }
    return true;
}
