// Loading Express, in order to managing HTTP behind the scenes.
const express = require('express');
const bodyParser = require('body-parser');

// Create a server
const app = express();

// Create the array of received tweets
const tweets = [];

// Instead of attaching listener, we can provide methods
// matching HTTP verbs on specific URL requests
app.get('/', function(req, res) { res.send('Welcome to Node Twitter'); })

// A POST route for posting tweets, with a middleware (bodyParser()) to stream
// the post data from the client and turn it in a JavaScript object
// It works only with POST encoded in json
app.post('/send', bodyParser.json(), function(req, res) {
    // express.bodyParser() adds a property to req called body, it
    // contains an object representing the post data
    if (req.body && req.body.tweet) { 
		  tweets.push(req.body.tweet);
      res.send( { status:"ok", message:"Tweet received" } );
    }
    else { res.send( {status:"nok", message:"No tweet received" } ); }
})

// a GET route to access all the tweets
app.get('/tweets', function(req,res) { res.send(tweets) });

app.listen(8000);