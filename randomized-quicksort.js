function quicksort(array, low, high) {
    if (low < high) {
        let pivotIndex = partition(array, low, high);
        quicksort(array, low, pivotIndex - 1);
        quicksort(array, pivotIndex + 1, high);
    }
}

function partition(array, low, high) {
    let pivotIndex = Math.floor(Math.random() * (high - low + 1)) + low;
    let pivot = array[pivotIndex];
    let i = low - 1;
    for (let j = low; j <= high; j++) { // Adjust loop condition to include high
        if (array[j] <= pivot) {
            i++;
            let temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
    let temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
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
    const result = func(...args);
    const end = performance.now();
    const runtime = end - start;
  
    console.log(`Function ${func.name} took ${runtime.toFixed(2)} milliseconds to run.`);
  
    return result;
}

for(let i=0; i<6; i++){
    let n = Math.pow(2, i) * 1000;
    let array = generateArray(n);
    measureRuntime(quicksort, array, 0, n-1)
}