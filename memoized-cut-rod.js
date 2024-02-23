//Find the best value achievable for cutting a rod into optimal pieces
function memoizedCutRod(p, n){  
    let r = new Array(n);
    for(let i=0; i<=n; i++){
        r[i] = Number.NEGATIVE_INFINITY;
    }
    return cutRodAux(p, n, r);
}

function cutRodAux(p, n, r){    //P is an array, p[i] is the price for piece of i inches, n is the length of the rod, q is where we store the results
    if(r[n] >= 0){
        return r[n];
    }
    let q;
    if(n === 0){
       q = 0;
    }
    else{
        q = Number.NEGATIVE_INFINITY;
    }
    for(let i=1; i<=n; i++){
        q = Math.max(q, p[i]+cutRodAux(p, n-i, r));
    }
    r[n] = q;
    return q;
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
    measureRuntime(memoizedCutRod, priceArray, i);
}