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

app.get('/doctors/:doctorId/slots', (req, res) => {
  const { doctorId } = req.params;
  const slot = openSlots[doctorId]
  const enrichedSlot = {
    id: slot.id,
    time: slot.time,
    _links: {
      book: {
        href: `/slots/${slot.id}`,
        rel: "Make appointment",
        method: "POST"
      }
    }
  };

  res.status(200).json({ openSlotList: enrichedSlot });
});


// A resource for each slot
app.post('/slots/:slotId', (req, res) => {
  const slotId = parseInt(req.params.slotId);
  const user = req.body.user;
  const slot = Object.values(openSlots).flat().find(s => s.id === slotId);
  if (!slot) { return res.status(404).json({ error: "Slot not found" }); }

  const appointment = {
    id: appointments.length + 1,
    slot,
    user
  };

  appointments.push(appointment);
  
  return res.json({ appointment });
});

// Start the appointment service server
app.listen(3000, () => {console.log('Level 3 API running on http://localhost:3000'); });