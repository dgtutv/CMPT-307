function measureRuntime(func, ...args) {
    const start = performance.now();
    const result = func(...args);
    const end = performance.now();
    const runtime = end - start;
  
    console.log(`Function ${func.name} took ${runtime.toFixed(2)} milliseconds to run.`);
  
    return result;
}