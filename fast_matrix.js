function generateMatrix(n, m) {
    let matrix = [];
    for (let i = 0; i < n; i++) {
        let currentRow = [];
        for (let j = 0; j < m; j++) {
            let currentElement = Math.floor(Math.random() * 10);
            currentRow.push(currentElement);
        }
        matrix.push(currentRow);
    }
    return matrix;
}

function printMatrix(matrix) {
    console.log();
    for (let i = 0; i < matrix.length; i++) {
        console.log(matrix[i].join('\t'));
    }
    console.log();
}

function matrix_multiply(A, B) {
    let n = A.length;
    let midpoint = n / 2;

    if (n === 1) {
        return [[A[0][0] * B[0][0]]];
    }

    let A11 = A.slice(0, midpoint).map(row => row.slice(0, midpoint));
    let A12 = A.slice(0, midpoint).map(row => row.slice(midpoint));
    let A21 = A.slice(midpoint).map(row => row.slice(0, midpoint));
    let A22 = A.slice(midpoint).map(row => row.slice(midpoint));

    let B11 = B.slice(0, midpoint).map(row => row.slice(0, midpoint));
    let B12 = B.slice(0, midpoint).map(row => row.slice(midpoint));
    let B21 = B.slice(midpoint).map(row => row.slice(0, midpoint));
    let B22 = B.slice(midpoint).map(row => row.slice(midpoint));

    let P1 = matrix_multiply(A11, matrix_subtract(B12, B22));
    let P2 = matrix_multiply(matrix_add(A11, A12), B22);
    let P3 = matrix_multiply(matrix_add(A21, A22), B11);
    let P4 = matrix_multiply(A22, matrix_subtract(B21, B11));
    let P5 = matrix_multiply(matrix_add(A11, A22), matrix_add(B11, B22));
    let P6 = matrix_multiply(matrix_subtract(A12, A22), matrix_add(B21, B22));
    let P7 = matrix_multiply(matrix_subtract(A11, A21), matrix_add(B11, B12));

    let C11 = matrix_add(matrix_subtract(matrix_add(P5, P4), P2), P6);
    let C12 = matrix_add(P1, P2);
    let C21 = matrix_add(P3, P4);
    let C22 = matrix_subtract(matrix_subtract(matrix_add(P5, P1), P3), P7);

    let C = [];
    for (let i = 0; i < midpoint; i++) {
        C[i] = C11[i].concat(C12[i]);
    }
    for (let i = 0; i < midpoint; i++) {
        C[midpoint + i] = C21[i].concat(C22[i]);
    }

    return C;
}

function matrix_add(A, B) {
    return A.map((row, i) => row.map((el, j) => el + B[i][j]));
}

function matrix_subtract(A, B) {
    return A.map((row, i) => row.map((el, j) => el - B[i][j]));
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
