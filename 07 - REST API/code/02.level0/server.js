const express = require('express');
const app = express();

app.use(express.json());

// Simulated database
const openSlots = [
  { id: 1, time: "2025-05-12T10:00:00" },
  { id: 2, time: "2025-05-12T11:00:00" }
];

// Simulated appointment storage
const appointments = [];

// RPC-like API for appointment service
app.post('/appointmentService', (req, res) => {

  const { method, payload } = req.body;

  // Retrieve available slots
  if (method === 'openSlotRequest') {
    res.json({ openSlotList: openSlots });
  } 

  // Handle appointment requests
  else if (method === 'appointmentRequest') {
    const { slotId, user } = payload;

    const slot = openSlots.find(s => s.id === slotId);
    if (!slot) { return res.status(400).json({ error: "Slot not available" }); }

    // Simulate appointment creation
    const appointment = {
      id: appointments.length + 1,
      slot,
      user
    };

    // Add appointment to storage
    appointments.push(appointment);

    // Reply with appointment details
    res.json({ appointment });
  } 
  
  // Handle unknown methods
  else { res.status(400).json({ error: 'Unknown method' });}
});

// Start the appointment service server
app.listen(3000, () => {console.log('Level 0 RPC API running on http://localhost:3000'); });