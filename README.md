# Suspense Defense (Custom C++)

A 2D roguelike tower-defense game built in a custom C++ engine with the Doodle framework (Mar–Jun 2023).  
This was a **team project at DigiPen (4 members)**. Players alternate between **daytime exploration** to gather resources and **nighttime defense** to protect the base. Defeating bosses unlocks stronger weapons, while monster colonies multiply dynamically each day, creating a risk–reward dilemma.

---

## Team
- **Hyeonjoon Nam (남현준)** — Technical Lead, Tester  
- **Junhyeong Kim (김준형)** — Test Lead, Tool Developer  
- **Youngho Kim (김영호)** — Producer, Build Engineer  
- **Taehoon Lim (임태훈)** — Design Lead, Systems Design  

---

## Technical Highlights
- **Mediator Pattern** to centralize collision, spawning, and state management → reduced duplication, improved maintainability.  
- **Procedural Map Generation** (cellular automata) for fresh layouts each run.  
- **A\*** pathfinding integrated for smarter enemy pursuit without frame drops.  

*(For portfolio context: Hyeonjoon Nam served as Tech Lead, responsible for most gameplay/system code and for coordinating tasks and bugs via Trello.)*

---

## How to Play
**Title Screen**  
- Move Up: `W`  
- Move Down: `S`  
- Select: `Enter`  
- Back to Title: `Esc`  

**In Game**  
- Move: `WASD`  
- Attack / Resource Collection: `Left Click`  
- Dash: `Right Click`  
- Teleport to Base: `B`  
- Switch to Close Attack: `Tab`  
- Switch Gun Type: `1–4`  

(Check in-game tutorial for more details.)

---

## Build / Run
- Visual Studio 2019+ (C++17), x64 Debug/Release
- Doodle framework required (provided by DigiPen)  
- Run from project root (adjust working directory if needed)

---

> ⚠️ This repository is for academic purposes at DigiPen Institute of Technology.  
> Proprietary frameworks/assets are excluded where necessary.  
> Credits to all teammates; see commit history for contributions.
