// JavaScript code for the approach

// Declare global cost matrix
const MAX = 1000;
let cost = new Array(MAX).fill(null).map(
	() => new Array(MAX).fill(0));

// Helper function to calculate the sum of frequencies from
// index i to j
function Sum(freq, i, j)
{
	let s = 0;
	for (let k = i; k <= j; k++)
		s += freq[k];
	return s;
}

// Recursive function to find the optimal cost of a BST
// using memoization
function optCost_memoized(freq, i, j)
{
	if (i < 0 || j < 0)
		return 0;
	// Reuse cost already calculated for the subproblems.
	// Since we initialize cost matrix with 0 and frequency
	// for a tree of one node, it can be used as a stop
	// condition
	if (cost[i][j])
		return cost[i][j];
	// Get sum of freq[i], freq[i+1], ... freq[j]
	let fsum = Sum(freq, i, j);

	// Initialize minimum value
	let Min = Infinity;

	// One by one consider all elements as
	// root and recursively find cost of
	// the BST, compare the cost with min
	// and update min if needed
	for (let r = i; r <= j; r++) {
		let c = optCost_memoized(freq, i, r - 1)
				+ optCost_memoized(freq, r + 1, j) + fsum;
		if (c < Min) {
			Min = c;
			// replace cost with new optimal calc
			cost[i][j] = c;
		}
	}

	// Return minimum value
	return cost[i][j];
}

// Main function to calculate the minimum cost of a BST
function optimalSearchTree(keys, freq, n)
{
	// Here array keys[] is assumed to be
	// sorted in increasing order. If keys[]
	// is not sorted, then add code to sort
	// keys, and rearrange freq[] accordingly.
	return optCost_memoized(freq, 0, n - 1);
}

// Usage example
let keys = [ 10, 12, 20 ];
let freq = [ 34, 8, 50 ];
let n = keys.length;

// cost[i][j] = Optimal cost of binary search
// tree that can be formed from keys[i] to keys[j].
// cost[0][n-1] will store the resultant cost
cost = new Array(MAX).fill(null).map(
	() => new Array(MAX).fill(0));

// For a single key, cost is equal to
// frequency of the key
for (let i = 0; i < n; i++)
	cost[i][i] = freq[i];

console.log("Cost of Optimal BST is "
			+ optimalSearchTree(keys, freq, n));
