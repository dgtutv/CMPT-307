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

function printMatrix(matrix) {
    console.log();
    for (let i = 0; i < matrix.length; i++) {
      console.log(matrix[i].join('\t')); // Join elements with tabs for better formatting
    }
    console.log();
}

function matrix_multiply(A, B){
    
}