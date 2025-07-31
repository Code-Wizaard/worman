# WORMAN 🛠️📁

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20Unix-lightgrey)](#)
[![Status](https://img.shields.io/badge/status-active-brightgreen)](#)
[![AUR](https://img.shields.io/badge/Available%20on-GitHub-orange)](https://aur.archlinux.org/packages/worman)
[![Made with ❤️](https://img.shields.io/badge/Made%20with-%E2%9D%A4-red)](#)

**Worman** is a terminal-based workspace wizard for developers that simplifies project initialization, Git integration, and structure creation. It supports multiple languages, project types, and offers an interactive, colorful CLI with autocomplete.

---

## 🚀 Features

- ⚙️ Create structured workspaces for C, C++, Python, Web, and more
- 🌐 Autocomplete for flags, languages, frameworks (via `readline`)
- 🧠 Optional Git initialization and remote linking
- ⬇️ Remote cloning support
- 🆕 `worman push` for auto-staging, committing, and pushing changes
- 🔥 Built-in `.gitignore` templates (dynamically fetched for efficiency)
- 🎨 ASCII art & colored terminal UI for better UX
- 📂 Supports optional target directory creation (`worman make /path/to/dir`)
- 🌐 Web template includes:
  - `index.html`
  - `css/style.css`
  - `js/script.js`  
  Fully linked and ready to go!

---

## 📦 Installation

Simply download the binary and place it in your system path.

```bash
sudo mv worman /usr/local/bin/
sudo chmod +x /usr/local/bin/worman
```

Now you can use `worman` anywhere from your terminal.

---

## 🧪 Example Usage

```bash
worman make                # Starts interactive wizard
worman make ~/dev/project # Creates workspace in ~/dev/project
worman push "Initial commit"  # Git stage + commit + push
```

---

## 🛠️ Planned Enhancements

- 🧱 Framework support (e.g. Tailwind, Bootstrap)
- 📁 Configurable templates per language
- 🧪 Test scaffolding generators
- 🔧 Custom commands & plugin support

---

## 🤝 Contributing

Pull requests are welcome! If you'd like to improve or extend Worman, feel free to fork and submit a PR.

---

## 📜 License

This project is licensed under the **GNU General Public License v3.0**.  
See the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.html) file for details.

---

**Happy Coding with WORMAN! 🚀**
