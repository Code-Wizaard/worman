#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

namespace fs = std::filesystem;
using namespace std;

// Terminal Colors
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

// Run shell command and return output
string run_cmd(const string& cmd) {
    FILE* fp = popen(cmd.c_str(), "r");
    if (!fp) return "ERROR";
    string result;
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp))
        result += buffer;
    pclose(fp);
    return result;
}

// ASCII Banner
void show_banner() {
    cout << CYAN;
    cout << " __        __   _                            \n";
    cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___   \n";
    cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  \n";
    cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/  \n";
    cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \n";
    cout << "              " << YELLOW << "W O R M A N" << RED << "  v0.0.1 🧙\n\n";
    cout << RESET;
}

// Download .gitignore
void download_gitignore(const string& language) {
    string url = "https://raw.githubusercontent.com/github/gitignore/main/" + language + ".gitignore";
    string cmd = "curl -s -o .gitignore " + url;
    cout << YELLOW << "Downloading .gitignore for " << language << "...\n" << RESET;
    if (system(cmd.c_str()) == 0)
        cout << GREEN << ".gitignore added.\n" << RESET;
    else
        cout << RED << "Download failed. Try valid language name.\n" << RESET;
}

// Git clone
void clone_repo(const string& url) {
    cout << YELLOW << "Cloning repository...\n" << RESET;
    cout << run_cmd("git clone " + url);
}

// Git push
void git_push(const string& msg) {
    string finalMsg = msg.empty() ? "Updated project via WORMAN ♻️" : msg;
    run_cmd("git add .");
    run_cmd("git commit -m \"" + finalMsg + "\"");
    cout << run_cmd("git push");
}

// Write file
void write_file(const fs::path& path, const string& content) {
    ofstream out(path);
    out << content;
}

// Create web workspace
void create_web_workspace(const fs::path& path) {
    fs::create_directories(path / "css");
    fs::create_directories(path / "js");
    fs::create_directories(path / "assets");

    write_file(path / "css" / "style.css", "body {\n    font-family: sans-serif;\n    margin: 0;\n    padding: 0;\n}\n");

    write_file(path / "js" / "script.js", "console.log('WORMAN Web Workspace Loaded');\n");

    write_file(path / "index.html", R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>WORMAN Web</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <h1>Welcome to WORMAN Web Workspace</h1>
    <script src="js/script.js"></script>
</body>
</html>
)");

    string fw;
    cout << CYAN << "Install CSS framework (tailwind/bootstrap)? (y/n)\n> " << RESET;
    cin >> fw;
    if (fw == "y" || fw == "Y") {
        cout << CYAN << "Choose framework (tailwind/bootstrap):\n> " << RESET;
        string framework;
        cin >> framework;
        if (framework == "tailwind") {
            ofstream html(path / "index.html", ios::trunc);
            html << R"(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>WORMAN Web</title>
  <script src="https://cdn.tailwindcss.com"></script>
</head>
<body class="p-5">
  <h1 class="text-primary">Welcome to WORMAN Web Workspace</h1>
  <script src="js/script.js"></script>
</body>
</html>
)";
            cout << GREEN << "Tailwind linked in index.html.\n" << RESET;
        } else if (framework == "bootstrap") {
            ofstream html(path / "index.html", ios::trunc);
            html << R"(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <title>WORMAN Web</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body class="p-5">
  <h1 class="text-primary">Welcome to WORMAN Web Workspace</h1>
  <script src="js/script.js"></script>
</body>
</html>
)";
            cout << GREEN << "Bootstrap linked in index.html.\n" << RESET;
        } else {
            cout << RED << "FRAMEWORK WRONG OR NOT SUPPORTED, SKIPPING..." << RESET;
        }
    }
}

// Create project structure
void create_structure(const string& lang, const fs::path& dir) {
    if (lang == "cpp") {
        fs::create_directories(dir / "src");
        fs::create_directories(dir / "include");
        fs::create_directories(dir / "build");
        fs::create_directories(dir / "bin");
        write_file(dir / "src" / "main.cpp", "#include <iostream>\nusing namespace std;\nint main() {\n    cout << \"Hello, WORMAN!\\n\";\n    return 0;\n}");
        write_file(dir / "Makefile", "all:\n\tg++ src/main.cpp -o bin/main");
    } else if (lang == "c") {
        fs::create_directories(dir / "src");
        fs::create_directories(dir / "include");
        fs::create_directories(dir / "build");
        fs::create_directories(dir / "bin");
        write_file(dir / "src" / "main.c", "#include <stdio.h>\nint main() {\n    printf(\"Hello, WORMAN!\\n\");\n    return 0;\n}");
        write_file(dir / "Makefile", "all:\n\tgcc src/main.c -o bin/main");
    } else if (lang == "python") {
        write_file(dir / "main.py", "print(\"Hello from WORMAN 🐍\")");
        write_file(dir / "requirements.txt", "# Add your dependencies here");
    } else if (lang == "html" || lang == "web" || lang == "site" || lang == "website") {
        create_web_workspace(dir);
    }
}

// Main wizard
void run_make_wizard(const fs::path& base_path = ".") {
    string project, lang;
    cout << GREEN << "Enter project name:\n> " << RESET;
    cin >> project;

    fs::path dir = base_path / project;
    fs::create_directories(dir);

    cout << GREEN << "Enter language:\n> " << RESET;
    cin >> lang;

    if (lang == "c++" || lang == "cxx") lang = "cpp";
    else if (lang == "py") lang = "python";
    else if (lang == "web" || lang == "website" || lang == "html" || lang == "site") lang = "html";

    create_structure(lang, dir);

    bool git_allowed = (lang != "html" && lang != "web" && lang != "site" && lang != "website");

    string git = "n";
    if (git_allowed) {
        cout << CYAN << "Initialize git? (y/n)\n> " << RESET;
        cin >> git;
        if (git == "y" || git == "Y") {
            run_cmd("cd " + dir.string() + " && git init");
            string addRemote;
            cout << "Add remote repo? (y/n)\n> ";
            cin >> addRemote;
            if (addRemote == "y" || addRemote == "Y") {
                string url;
                cout << "Enter remote URL:\n> ";
                cin >> url;
                run_cmd("cd " + dir.string() + " && git remote add origin " + url);
            }
        }
    }

    if (git == "y" || git == "Y") {
        string ignore;
        cout << CYAN << "Add .gitignore? (y/n)\n> " << RESET;
        cin >> ignore;
        if (ignore == "y" || ignore == "Y") {
            fs::current_path(dir);
            download_gitignore(lang);
        }
    }

    cout << GREEN << "Project setup complete at: " << dir << " ✅\n" << RESET;
}

// Main
int main(int argc, char* argv[]) {
    show_banner();

    if (argc == 1) {
        cout << "Usage:\n"
             << "  worman make [--path /target]   Start wizard and optionally set path\n"
             << "  worman clone <url>             Clone git repo\n"
             << "  worman push [msg]              Git add/commit/push\n"
             << "  worman gitignore <lang>        Download .gitignore\n";
        return 0;
    }

    string arg1 = argv[1];

    if (arg1 == "make") {
        fs::path path = ".";
        if (argc == 4 && string(argv[2]) == "--path") {
            path = argv[3];
        }
        run_make_wizard(path);
    }
    else if (arg1 == "clone" && argc >= 3) {
        clone_repo(argv[2]);
    }
    else if (arg1 == "push") {
        string msg = (argc >= 3) ? argv[2] : "";
        git_push(msg);
    }
    else if (arg1 == "gitignore" && argc >= 3) {
        download_gitignore(argv[2]);
    }
    else if (arg1 == "--help") {
        cout << "Usage:\n"
             << "  worman make [--path /target]   Start wizard and optionally set path\n"
             << "  worman clone <url>             Clone git repo\n"
             << "  worman push [msg]              Git add/commit/push\n"
             << "  worman gitignore <lang>        Download .gitignore\n";
        return 0;
    }
    else {
        cout << RED << "Unknown command.\n" << YELLOW << "HINT: TRY " << CYAN << "`worman --help`" << RESET;
    }

    return 0;
}