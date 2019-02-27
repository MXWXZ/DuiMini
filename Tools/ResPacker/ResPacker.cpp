/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/20
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <miniz/miniz.h>
#include <cxxopts/cxxopts.hpp>
using namespace std;

const char* kFileCmd = "files";

unsigned char* ReadFile(string filename, long* size);
bool WriteFile(string filename, void* buffer, long size);

int main(int argc, char* argv[]) {
    try {
        bool isunpack = false, isnobackup = false;
        string exefile, zipfile;

        cxxopts::Options options(argv[0], "ResPacker CLI options");
        options.positional_help("[exefile] [zipfile]").show_positional_help();

        // clang-format off
        options.add_options()("h,help", "Print help")
                             ("nobackup", "Do not make backup file",
                              cxxopts::value<bool>(isnobackup))
                             ("u,unpack", "Unpack mode",
                              cxxopts::value<bool>(isunpack))
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
                if (!isunpack) {
                    cout << "zipfile is needed." << endl;
                    return 1;
                }
                exefile = result[kFileCmd].as<vector<string>>()[0];
                break;
            case 2:
                if (isunpack) {
                    cout << "Unknown argument "
                         << result[kFileCmd].as<vector<string>>()[1] << endl;
                    return 1;
                }
                exefile = result[kFileCmd].as<vector<string>>()[0];
                zipfile = result[kFileCmd].as<vector<string>>()[1];
                break;
            default:
                cout << "Too many arguments!" << endl;
                return 1;
        }

        // working
        bool error = true;
        long zipsize, exesize;
        unsigned char *zip = nullptr, *exe = nullptr, fileid[2];
        unsigned char resid[] = {0x55, 0x49};  // Identifier "UI"
        FILE* fp = nullptr;

        if (isunpack) {
            // reading packed exefile
            cout << "Reading " << exefile << endl;
            if (!(fp = fopen(exefile.c_str(), "rb"))) {
                cout << exefile << " can't access!" << endl;
                goto CLEANUP;
            }

            // reading original exefile
            fseek(fp, -(long)sizeof(exesize), SEEK_END);
            if (fread(&exesize, sizeof(exesize), 1, fp) != 1) {
                cout << "Reading filesize error!" << endl;
                goto CLEANUP;
            }
            fseek(fp, 0, SEEK_SET);
            exe = new unsigned char[exesize];
            if (fread(exe, exesize, 1, fp) != 1) {
                cout << "Reading " << exefile << " error!" << endl;
                goto CLEANUP;
            }

            // varify id
            if (fread(fileid, 2, 1, fp) != 1) {
                cout << "Reading identifier error!" << endl;
                goto CLEANUP;
            }
            if (fileid[0] != resid[0] ||
                fileid[1] != resid[1]) {  // not packed exe
                cout << "Varify error! Perhaps not UI packed exefile." << endl;
                goto CLEANUP;
            }

            // reading zipfile
            if (fread(&zipsize, sizeof(zipsize), 1, fp) != 1) {
                cout << "Reading filesize error!" << endl;
                goto CLEANUP;
            }
            zip = new unsigned char[zipsize];
            if (fread(zip, zipsize, 1, fp) != 1) {
                cout << "Reading " << zipfile << " error!" << endl;
                goto CLEANUP;
            }
            if (fclose(fp)) {
                cout << "Close " << exefile << " failed!" << endl;
                goto CLEANUP;
            }

            // seperate files
            if (!WriteFile(exefile + ".src", exe, exesize))
                goto CLEANUP;
            if (!WriteFile(exefile + ".zip", zip, zipsize))
                goto CLEANUP;
        } else {
            // reading zip and exe file
            zip = ReadFile(zipfile, &zipsize);
            if (!zip)
                goto CLEANUP;

            exe = ReadFile(exefile, &exesize);
            if (!exe)
                goto CLEANUP;

            // make bakfile
            if (!isnobackup)
                if (!WriteFile(exefile + ".bak", exe, exesize))
                    goto CLEANUP;

            // append exefile
            cout << "Appending to " << exefile << " ..." << endl;
            if (!(fp = fopen(exefile.c_str(), "ab"))) {
                cout << exefile << " can't access!" << endl;
                goto CLEANUP;
            }
            if (fwrite(resid, 2, 1, fp) != 1 ||
                fwrite(&zipsize, sizeof(zipsize), 1, fp) != 1 ||
                fwrite(zip, zipsize, 1, fp) != 1 ||
                fwrite(&exesize, sizeof(exesize), 1, fp) != 1) {
                cout << "Writting to " << exefile << " failed!" << endl;
                goto CLEANUP;
            }
            if (fclose(fp)) {
                cout << "Close " << exefile << " failed!" << endl;
                goto CLEANUP;
            }
        }

        fp = nullptr;
        error = false;  // ALL OK
        cout << "Process successfully!" << endl;
    CLEANUP:
        if (fp)
            fclose(fp);
        delete[] zip;
        delete[] exe;
        if (error)
            return 1;
    } catch (const cxxopts::OptionException& e) {
        cout << "Error parsing options: " << e.what() << endl;
        return 1;
    }
    return 0;
}

unsigned char* ReadFile(string filename, long* size) {
    cout << "Reading " << filename << " ..." << endl;
    FILE* fp;
    if (!(fp = fopen(filename.c_str(), "rb"))) {
        cout << filename << " can't access!" << endl;
        return nullptr;
    }
    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    rewind(fp);
    auto file = new unsigned char[*size];
    if (fread(file, *size, 1, fp) != 1) {
        cout << "Reading " << filename << " error!" << endl;
        delete[] file;
        fclose(fp);
        return nullptr;
    }
    if (fclose(fp)) {
        cout << "Close " << filename << " failed!" << endl;
        delete[] file;
        return nullptr;
    }
    return file;
}

bool WriteFile(string filename, void* buffer, long size) {
    cout << "Writting to " << filename << " ..." << endl;
    FILE* fp;
    if (!(fp = fopen(filename.c_str(), "wb"))) {
        cout << filename << " can't access!" << endl;
        return false;
    }
    if (fwrite(buffer, size, 1, fp) != 1) {
        cout << "Writting to " << filename << " failed!" << endl;
        fclose(fp);
        return false;
    }
    if (fclose(fp)) {
        cout << "Close " << filename << " failed!" << endl;
        return false;
    }
    return true;
}
