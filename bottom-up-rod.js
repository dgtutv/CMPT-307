function bottomUpRod(p, n){
    let r = new Array(n);
    r[0] = 0;
    for(let j=1; j<=n; j++){
        let q = Number.NEGATIVE_INFINITY;
        for(let i=1; i<=j; i++){
            q = Math.max(q, p[i]+r[j-i]);
        }   
        r[j] = q;
    }
    return r[n];
}

function measureRuntime(func, ...args) {
    const start = performance.now();
    const result = func(...args);
    const end = performance.now();
    const runtime = end - start;
  
    console.log(`Function ${func.name} took ${runtime.toFixed(2)} milliseconds to run and returned ${result}.`);
  
    return result;
}

let priceArray = [0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150]; 
for(let i=5; i<35; i+=5){
    console.log(`Rod length: ${i}`);
    measureRuntime(bottomUpRod, priceArray, i);
}