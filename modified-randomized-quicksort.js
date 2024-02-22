function quicksortModified(array, low, high, k) {
    if (low < high) {
        if (high - low + 1 <= k) { 
            insertionSort(array, low, high);
        } else {
            let pivotIndex = partition(array, low, high);
            quicksortModified(array, low, pivotIndex - 1, k);
            quicksortModified(array, pivotIndex + 1, high, k);
        }
    }
}

function insertionSort(array, low, high) {
    for(let i = low+1; i <= high; i++){
        let key = array[i];
        let j = i-1;
        while(j >= low && array[j] > key){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

function partition(array, low, high){
    let pivotIndex = Math.floor(Math.random() * (high - low + 1)) + low;
    let pivot = array[pivotIndex];
    let i = low-1;
    for(let j=low; j < high; j++){
        if(array[j] <= pivot){
            i++;
            let temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
    let temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;
    return i+1;
}

function generateArray(n){
    let A = new Array;
    for(let i=0; i<n; i++){
        let currentValue = Math.random();
        A[i] = currentValue;
    }
    return A;
}

function measureRuntime(func, ...args) {
    const start = performance.now();
    func(...args); // Call the function to be measured
    const end = performance.now();
    const runtime = end - start;
    const result = `${runtime.toFixed(2)} milliseconds`;  
    return {runtime: runtime, result: result}; // Return both runtime and result
}

let results = {};
const maxIterations = 10; // Limit the number of iterations for each value of k
for(let i=0; i<6; i++){
    let n = Math.pow(2, i) * 1000;
    let nResults = [];
    let totalRuntime = 0; // Initialize total runtime
    let stepSize = Math.floor(n / maxIterations); // Calculate step size
    for(let k=0; k<n; k+=stepSize){
        if (k === 0) {
            // Skip k = 0 since it's not meaningful in this context
            continue;
        }
        let array = generateArray(n);
        let currentResult = measureRuntime(quicksortModified, array, 0, n-1, k);
        totalRuntime += currentResult.runtime; // Add current runtime to total
        nResults.push({k: k, runtime: currentResult.result});
    }

    // Calculate average runtime
    let averageRuntime = totalRuntime / (nResults.length || 1); // Avoid division by zero
    
    // Push average runtime to nResults array
    nResults.push({k: 'Average', runtime: `${averageRuntime.toFixed(2)} milliseconds`});
    
    // Store results for this value of n
    results[n] = nResults;
}

// Print results in a table-like structure
console.log("Results:");
console.log("---------------------------------------------------------------------");
console.log("|      n      |      k      |       Runtime (ms)            |");
console.log("---------------------------------------------------------------------");
for (let n in results) {
    results[n].forEach(result => {
        console.log(`| ${n.toString().padStart(12)} | ${result.k.toString().padStart(12)} | ${result.runtime.padStart(30)} |`);
    });
    console.log("---------------------------------------------------------------------");
}
