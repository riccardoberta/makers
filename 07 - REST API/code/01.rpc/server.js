const express = require('express');
const app = express();

app.use(express.json());

// Example RPC method
function add(a, b) {
  return a + b;
}

// RPC endpoint
app.post('/rpc', (req, res) => {
  const { method, params } = req.body;
  
  // Validate method and parameters
  if (method === 'add' && Array.isArray(params) && params.length === 2) {
    const result = add(params[0], params[1]);
    res.json({ result });
  } 

  // Handle other methods or invalid input
  else {
    res.status(400).json({ error: 'Invalid method or parameters' });
  }
});

// Start the server
app.listen(3000, () => { console.log('RPC server running at http://localhost:3000');});