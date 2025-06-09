


# Axis-Aligned Enclosure Optimization

This project solves the **Axis-Aligned Enclosure Optimization** problem:  
Given `N` buildings on a 2D plane with weights and coordinates, find a **simple, axis-aligned rectangle** that encloses **at least K buildings**, minimizing the total cost defined as:

> **Total Cost = Perimeter of Rectangle + Sum of Weights of Enclosed Buildings**

---

## 🧠 Problem Statement

You are tasked with urban zoning in a futuristic city. You must design an **axis-aligned rectangle** (with sides parallel to the X and Y axes) that:

- Is a **closed, non-self-intersecting polygon**
- **Encloses at least K buildings**, where a building is considered enclosed if it lies strictly inside or on the boundary
- **Minimizes the total cost** as defined above

---

## 📥 Input Format

N K  
x₁ y₁ w₁  
x₂ y₂ w₂  
...  
xₙ yₙ wₙ

- `N`: Number of buildings (1 ≤ N ≤ 10⁴)  
- `K`: Minimum number of buildings to enclose (1 ≤ K ≤ N)  
- Each building has:  
  - `(xᵢ, yᵢ)`: Position on grid (0 ≤ xᵢ, yᵢ ≤ 10⁴)  
  - `wᵢ`: Cost of enclosing the building (can be negative)

---

## 📤 Output Format

C
x1 y1 x2 y1
x2 y1 x2 y2
x2 y2 x1 y2
x1 y2 x1 y1

- `C`: Minimum total cost (printed with at least 6 digits after the decimal)
- Next 4 lines describe the rectangle edges in order (either horizontal or vertical)

---

## ⚙️ Approach

### ✅ Sliding Window + Multiset

- Sort buildings by x-coordinate
- Use a sliding window approach to explore all (x1, x2) ranges
- Maintain two multisets to track:
  - Top K buildings with lowest weights (`low`)
  - Remaining buildings (`high`)
- Use a rebalancing function to ensure `low` always has the best K-weight subset

### ✅ Y-axis Optimization

- Dynamically compute the y-range using the selected top-K buildings
- Use multiset to retrieve min/max y-values in O(log K)

### ✅ Cost Calculation

- Compute cost using:
cost = 2 × (x2 − x1 + y2 − y1) + sum of K weights


- Update the best rectangle when a lower cost is found

---

## 💡 Key Features

- Efficient for large inputs (up to 10⁴ buildings)
- Uses STL (`multiset`, lambdas, fast I/O)
- Floating-point precision maintained
- Produces clean polygon edge list in order

---

## 🧪 Sample

### Input
5 3
1 1 5
2 2 3
4 4 2
6 1 1
3 3 4

### Output
20.000000
2 2 4 2
4 2 4 4
4 4 2 4
2 4 2 2


---

## 🛠️ Requirements

- C++11 or later

### ✅ Compile
```bash
g++ -std=c++11 -O2 -o enclosure enclosure.cpp
### ▶️ Run
```bash
./enclosure < input.txt
📁 AxisAlignedEnclosure/
├── enclosure.cpp      # Main source code
├── README.md          # Project documentation
└── input.txt          # (Optional) Sample input

