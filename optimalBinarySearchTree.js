class Node {
    constructor(key) {
        this.key = key;
        this.left = null;
        this.right = null;
    }
}

function constructOptimalBST(p, q, root, i, j) {
    if (i > j) return null;
    let k = root[i][j];
    let node = new Node(k);
    node.left = constructOptimalBST(p, q, root, i, k - 1);
    node.right = constructOptimalBST(p, q, root, k + 1, j);
    return node;
}

function displayOptimalBST(root) {
    if (root === null) return;
    console.log("Root of the tree is", root.key);
    if (root.left) console.log("Left child of", root.key, "is", root.left.key);
    if (root.right) console.log("Right child of", root.key, "is", root.right.key);
    displayOptimalBST(root.left);
    displayOptimalBST(root.right);
}

function optimalBinarySearchTree(p, q, n) {
    // Create arrays to store cost and root
    let cost = new Array(n + 2).fill().map(() => new Array(n + 1).fill(0));
    let root = new Array(n + 2).fill().map(() => new Array(n + 2).fill(0));

// Initialize base cases
for (let i = 1; i <= n + 1; i++) {
    cost[i][i - 1] = q[i - 1];
    root[i][i - 1] = i - 1;
}

    // Perform dynamic programming
    for (let len = 1; len <= n; len++) {
        for (let i = 1; i <= n - len + 1; i++) {
            let j = i + len - 1;
            cost[i][j] = Infinity;

            // Calculate cost and root for subtree [i, j]
            for (let r = i; r <= j; r++) {
                let c = cost[i][r - 1] + cost[r + 1][j] + sum(p, q, i, j);
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    // Construct optimal binary search tree
    let rootOfOptimalBST = constructOptimalBST(p, q, root, 1, n);

    // Display the optimal binary search tree
    console.log("Optimal Binary Search Tree:");
    displayOptimalBST(rootOfOptimalBST);

    // Total cost of optimal binary search tree
    let totalCost = cost[1][n];
    return totalCost;
}

function sum(p, q, i, j) {
    let sum = 0;
    for (let k = i; k <= j; k++) {
        sum += p[k];
    }
    for (let k = i - 1; k <= j; k++) {
        sum += q[k];
    }
    return sum;
}

// Example usage
let p = [0, 0.04, 0.06, 0.08, 0.02, 0.10, 0.12, 0.14];
let q = [0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05];
let n = p.length - 1; // Number of keys

let totalCost = optimalBinarySearchTree(p, q, n);
console.log("Total cost of optimal binary search tree:", totalCost);
