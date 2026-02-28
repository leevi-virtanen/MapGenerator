
# Procedural 2D Room Generator

This project is a C++ based procedural generation system for placing interconnected rooms on a 2D grid. It uses matrices to represent individual rooms and a larger matrix to represent the world map. The algorithm pseudo-randomly places rooms by validating door alignments and checking for overlapping spaces.


---

## Core Concepts

### Room Definitions & Tile Values

Rooms are defined as matrices (default 3x3) where numbers represent different tile types. The values range from 0 to 5:

* **`0`**: Empty space.
* **`1`**: Wall (fills the spaces that doors do not).
* **`2`**: Door facing **Right**.
* **`3`**: Door facing **Down**.
* **`4`**: Door facing **Left**.
* **`5`**: Door facing **Up**.

*Note: A single cell can only hold one door. The coordinate (0,0) represents the top-left of the room matrix.*

---

## Classes

### `coordinate`

A simple utility class for storing 2D grid positions.

* **Properties:**
* `int x`: The X-coordinate (horizontal).
* **`int y`**: The Y-coordinate (vertical).


* **Constructor:** `coordinate(int coordx, int coordy)` initializes the object with the given values.

### `PlacedRoom`

A data container used for tracking rooms after they have been successfully placed on the map.

* **Properties:**
* `int roomId`: The index/ID of the room template used.
* `coordinate coord`: The top-left position where the room was placed on the map.
* `int rotation`: The rotation state of the room (0-3, corresponding to 0°, 90°, 180°, and 270°).


* **Constructor:** Initializes the tracking data.

### `twoarray`

A 2D array abstraction built on top of a 1D `std::vector<int>`. Used for both individual rooms and the global map.

* **Properties:**
* `int size`: The width and height of the grid (always square).
* `std::vector<int> array`: The underlying flattened 1D array.


* **Constructors:**
* `twoarray(int height)`: Initializes a grid of `height` x `height` filled with `0`s. Used primarily for the main map.
* `twoarray()`: Initializes a grid based on the global constant `cellsize` (defaults to 3x3). Used for room templates.


* **Methods:**
* **`int get(coordinate coord)`**: Retrieves the tile value at a specific coordinate. **Returns `-1**` if the requested coordinate is out of bounds.
* **`bool set(coordinate coord, int input)`**: Sets the tile value at a specific coordinate. **Returns `false**` if the coordinate is out of bounds, otherwise returns `true`.



---

## Functions

### `twoarray roomset(std::vector<int> row1, std::vector<int> row2, std::vector<int> row3)`

A helper function to quickly define a 3x3 room matrix from three vectors representing its rows.

* **Returns**: A populated `twoarray` object.

### `void place(twoarray& room, twoarray& map, coordinate coord)`

Unconditionally writes a room's data into the map at the given coordinate.

* **Logic**: It iterates through the room's matrix and copies any non-zero value directly onto the map.

### `bool placeablecheck(twoarray& room, twoarray map&, coordinate coord)`

Validates whether a room can be legally placed at a specific coordinate on the map.

* **Logic**:
1. **Overlap Check**: It fails (`returns false`) if a non-zero tile in the room overlaps with an already existing non-zero tile on the map.
2. **Door Alignment Check**: It checks if at least one door in the room correctly aligns with a corresponding, opposite-facing door on the map (e.g., a "Right" door `2` must touch a "Left" door `4`).


* **Returns**: `true` if there are no overlaps AND at least one door connects correctly; otherwise `false`.

### `void printtwoarray(twoarray room)`

Iterates through a `twoarray` (usually the main map) and prints its contents to the standard output as a grid of numbers.

### `twoarray rotate(twoarray room)`

Rotates a room's matrix 90 degrees clockwise.

* **Logic**: It transposes the matrix, reverses the columns, and then mathematically updates the door values so they point in the correct new directions (e.g., a "Right" door `2` becomes a "Down" door `3`).
* **Returns**: A new `twoarray` containing the rotated room.

### `twoarray rotate(twoarray room, int times)`

An overloaded helper function that rotates a room multiple times.

* **Parameters**: `times` dictates how many 90-degree clockwise rotations to apply.

### `bool fullPlaceAlgorithm(int roomId, twoarray& room, twoarray& map, coordinate coord, std::vector<PlacedRoom>& trackingList)`

The core placement attempt algorithm.

* **Logic**: Given a target coordinate, it searches a 3x3 area around it. For each cell in that area, it tests all 4 possible rotations of the room. If a valid configuration is found (using `placeablecheck`), it places the room, adds it to the `trackingList`, and halts the search.
* **Returns**: `true` if the room was successfully placed, `false` otherwise.

---

## How It Works (Main Loop)

1. **Initialization**: A 30x30 map is created, alongside a vector of 6 predefined 3x3 room templates.
2. **Seed**: The first room is forcefully placed at the center of the map `(15, 15)` to act as an anchor.
3. **Generation Loop**:
* The algorithm gathers all coordinates on the map and shuffles them randomly.
* It iterates through these random coordinates, picking a random room template.
* It uses `fullPlaceAlgorithm` to try and attach the new room to existing architecture.
* The loop continues until a full pass over the map yields no new room placements.


4. **Output**: The final grid is printed to the console, followed by a summary list of all placed rooms, their exact coordinates, and their rotations.

---
