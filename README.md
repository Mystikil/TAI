# TAI - The AI-Enhanced Forgotten Server

**TAI** is a heavily customized fork of [The Forgotten Server (TFS)](https://github.com/otland/forgottenserver), featuring modular enhancements such as AI-based monster logic, instanced dungeons, profession-based skills, and an optional classless character system. It’s designed to offer advanced gameplay mechanics while keeping extensibility and readability in mind—even for young developers.

---

## 🚀 Features

### 🧠 Advanced AI System
- Built-in [Behavior Tree](docs/ai_scripting.md)-based AI framework for monsters and NPCs.
- Supports conditional logic like fleeing when below HP threshold, chasing patterns, and more.
- Easily scriptable in C++ or Lua with modular nodes.

### ⚔️ Classless Character Progression (Optional)
- Controlled via `enableClasslessSystem` in `config.lua`.
- Instead of vocations, players gain free attribute points every level.
- Customizable via `pointsPerLevel`.

### 🧪 Alchemy System
- Craft potions and materials using player-discovered or scripted recipes.
- Recipes are Lua-defined in `data/scripts/alchemy/recipes.lua`.
- Triggered via containers defined in `alchemy.lua`.

### 🛠 Additional Professions & Skills
- Includes Alchemy, Mining, Cooking, Woodcutting, Tracking, Carpentry, Survival, and more.
- Fully documented in `docs/new_skills.md`.
- Easily extendable via Lua.

### 🧩 Instanced Dungeons
- Enter dungeons from tiles or triggers (`data/actions/scripts/instances.lua`).
- Procedurally supports map chunks.
- Auto-scales with party stats and supports dynamic difficulty escalation.
- Auto-closes when boss is defeated.

### 🌦️ Weather Prototype (Optional)
- Toggleable weather system (fog/rain).
- Easily expandable from prototype.

### 🛡 Monster Scaling & Overspawn
- `monsterGroupScaling`, `monsterOverspawn` available in `config.lua`.
- Automatically scales monsters in groups.

### 🔐 2FA Support
- Optional Two-Factor Authentication via `enableTwoFactorAuth` config flag.

---

## 📦 Installation & Compilation

### 📍 Dependencies
- [CMake](https://cmake.org/)
- [vcpkg](https://github.com/microsoft/vcpkg)
- Boost, OpenSSL, Lua, MariaDB (managed via vcpkg)
- Visual Studio 2022 (Windows) or GCC/Clang (Linux)

---

## 🐧 Linux Setup (Debian/Ubuntu)

```bash
# Install tools
sudo apt update && sudo apt install git cmake build-essential libssl-dev zlib1g-dev

# Clone repo
git clone https://github.com/Mystikil/TAI.git
cd TAI

# Set up vcpkg dependencies
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install

# Build project
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake
make -j$(nproc)
🪟 Windows Setup (VS2022)
Clone the repo:

bash
Copy
Edit
git clone https://github.com/Mystikil/TAI.git
Install vcpkg and bootstrap it.

Open vc17/theforgottenserver.sln in Visual Studio 2022.

Set the startup project to theforgottenserver, then:

Right-click > Restore vcpkg dependencies

Build > Build Solution (Release or Debug)

⚙️ Configuration Guide
Edit your config.lua file to enable/disable key systems:

lua
Copy
Edit
-- Classless System
enableClasslessSystem = true
pointsPerLevel = 5

-- AI
enableBehaviorTreeAI = true

-- Dungeon Instances
enableInstancing = true

-- Monster Group Scaling
monsterGroupScaling = true
monsterGroupAttackScale = 20
monsterGroupDefenseScale = 20

-- 2FA
enableTwoFactorAuth = true
🧪 Creating New Dungeon Instances
Dungeon instances can be triggered by tiles or actions:

Edit data/actions/scripts/instances.lua to define entry logic.

Configure each dungeon chunk via data/instances/instance_config.lua.

Each instance includes:

Map chunk reference

Monster difficulty scaling

Boss defeat triggers to auto-close instance

Rare mineral/stone spawn logic

📄 Documentation
docs/features.md: Full feature list

docs/ai_scripting.md: Behavior tree system

docs/classless.md: Classless character logic

docs/alchemy.md: Alchemy recipes and usage

docs/new_skills.md: All custom profession skills

🤝 Contributions
You're welcome to fork, refactor, and submit PRs! Add support for:

More AI behaviors

Additional instance logic

UI/UX improvements for accessibility

Better docs for young or new developers

📜 License
This project is open-source and follows the original TFS license.
