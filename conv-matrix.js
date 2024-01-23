function generateMatrix(n, m){
    let matrix = [];
    for(let i=0; i<n; i++){
        let currentRow = [];
        for(let j=0; j<m; j++){
            let currentElement = Math.floor(Math.random() * 10);
            currentRow.push(currentElement);
        }
        matrix.push(currentRow);
    }
    return matrix;
}

function matrix_multiply(A, B){
    let newMatrix = [];
    for(let i=0; i<A.length; i++){
        let currentRow = [];
        for(let j=0; j<A.length; j++){
            let currentElement = 0;
            for(let k=0; k<A.length; k++){
                currentElement = currentElement + A[i][k] * B[k][j];
                
            }   
            currentRow.push(currentElement);       
        }
        newMatrix.push(currentRow);
    }
    return newMatrix;
}

function printMatrix(matrix) {
    console.log();
    for (let i = 0; i < matrix.length; i++) {
      console.log(matrix[i].join('\t')); // Join elements with tabs for better formatting
    }
    console.log();
}

function measureRuntime(func, ...args) {
    const start = performance.now();
    const result = func(...args);
    const end = performance.now();
    const runtime = end - start;
  
    console.log(`Function ${func.name} took ${runtime.toFixed(2)} milliseconds to run.`);
  
    return result;
}

for(let i=4; i<11; i++){
    console.log(`i: ${i}`);
    let n = Math.pow(2, i);
    let A = generateMatrix(n, n);
    let B = generateMatrix(n, n);
    let C = measureRuntime(matrix_multiply, A, B); 
}