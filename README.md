# Info
This project was created for [NPRG041](https://www.ksi.mff.cuni.cz/teaching/nprg041-web/) class at Charles University Faculty of Mathematics and Physics.

**Author:** Vojtěch Pröschl
# User Documentation
## Dependencies
Required libraries:
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)

## Install
1) Clone this repository
2) Download Eigen library and place it into dependencies directory
3) Compile
4) Run

## Using
### Main menu
Main menu has three options, each of them is labeled with a number. To select a specific option type the number and press enter.

---
### Solver menu
Purpose of this menu is to create solvers which affect appearance of simulation. There are 4 available solvers, you can add as many of them as you want - using multiple solvers of the same type allows you to create complexity.

#### Commands:
- `back` - return to the parent menu
- `edit solver {solver index}` - opens settings menu of the selected solver
- `add solver {soler name}` - adds new solver of desired type
- `remove solver {solver index}` - removes selected solver

*Available solvers:*
### Source
This solver is responsible for adding particles into the simulation.

#### Options:
- **Count:** Amount of particles sourced per second
- **Position:** Position of the source in R3
- **Velocity range X,Y,Z:** Minimal and maximal velocity in each axis (values are chosen stochastically in the desired range)
- **Size range:** Minimal and maximal size of the particle - together with density this affects drag solver
- **Density range:** Purpose of this attribute is to control density of the particles, minimal and maximal value - it affects drag solver.

### Gravity
Purpose of this solver is to accelerate particles in a certain direction

#### Options:
- **Force:** Force vector from R3 which is added to the particles to accelerate their velocity

### Turbulence
Purpose of this vector is to accelerate particles in pseudo-random directions (e.g. emulating wind).

#### Options:
- **Amplitude:** Force multiplier
- **Voxel Size:** Size of the voxels generating the noise field (smaller value => higher noise frequency)

### Drag
Purpose of this solver is to slow down particles based on their speed, size and density.

#### Options:
- **Fluid density:** Purpose of this attribute is to increase/decrease drag effect (greater values => more drag force)

---

### Simulation Editor Menu
Purpose of this menu is to control main simulation settings.

#### Options:
- **Duration:** Duration of the simulation in seconds
- **Substeps:** Amount of simulated frames per one rendered frame (higher values => smoother and slower simulation)
- **Framerate:** Desired amount of frames per second

---

### Simulation Runner Menu
Purpose of this menu is to run and render the simulation.

Important directories:
- Output/Cache - Internal cache folder
- Output/Geometry - Sequence of simulation frames in .obj format (run)
- Output/Render - Sequence of simulation frames in .pbm (debug render)

#### Commands:
- **run** - Run the simulation, the simulation creates sequence of .obj files which you can use to playback the simulation in 3D animation software
- **debug render {res_x} {res_y} {scale}** - Renders the simulation (it has to be cached). Res_x,y is resolution of the .pbm files, scale is "zoom" of the render. Simple orthogonal projection.
---
---
# Technical Documentation
## Editor
This part of the program is responsible for the user interaction and creation of the simulation based on the user input.
### C: Editor
This class is running in loop to control lifecycle of the software. At each step it reads one line from the stdin and adjusts operations based on that.

### C: Menu
Menu is common ancestor for all menu classes, they're able to solve request and display its contents.
**Included menus**
- MainMenu ... Switching between more specific menus
- SimulationEditorMenu ... Adjusting simulation settings
- SolverMenu ... Menu that is used to add/remove/edit solvers
- SolverSettingsMenu ... Menu that is created automatically for each solver based on the **SolverSettings** class, it is used to change settings of individual solvers

At each point in the program lifetime the editor has a certain menu pointer, each menu besides the main has parent poiter, which they return when user uses the `back` command.

## Shared
This part of program contains functions and classes, that are used by both the Editor and the Simulation part.

### C: Settings
Settings is a common ancestor of all settings classes (e.g. SimulationSettings,SourceSolverSettings...). It has two important function - set_contents and get_contents. Those two functions are used through the software to store/load settings about solvers, simulation etc.

### F: SmartConversion
Smart conversions are utility functions, that convert data from/to string using << operator. They're templated and can be used to get Eigen::Vector of specific types.

## Simulation
This part of the program is responsible for the simulation itself. Simulation is done in three steps:
1. Pre-Solve
2. Mid-Solve
3. Post-Solve

Most of the solvers should be in the mid-solve category, pre-solving is for example for sourcing particles, which will then be affected by the mid-solving stage. Post solving is for solvers that could be added in the future e.g. collision detection, which have to be solved the last.

Simulation is caching frames once they're computed (substeps aren't stored, they are only internal).

### Solvers
Solvers get reference to vector of particles, which they're allowed to change in some way. For example source solver adds particles to that vector and sets their initial attributes.
Each solver has to have its settings class and it has to implement constructor and solve function. Depending on the solve type (pre/mid/post) you must use parent class. If you want the solver to be visible in the TUI, you have to add it to functions which are in the SolverMenu and in order for it to work you must add it to functions in simulation file - use existing solvers as a reference.

### C: Solver
Solver is common ancestor to all solvers. Each solver must take substeps and framerate into consideration!

### C: Cache
Cache is class that is responsible for particle serialization/deserialization, caching the frames into cache folder and saving the frames in the obj format. Each particle is stored into both of these formats once simulation computes the frame.

### C: Particle
Particle is class (struct) that is used to represent basic element of the simulation. It has multiple geometric attributes, which are changed during the simulation (e.g. position, velocity...).

## Render
In render folder you can find the following class:

### C: DebRenderer
This class is responsible for saving cached particles as .pbm files, which is a simple 1bit bitmap format.