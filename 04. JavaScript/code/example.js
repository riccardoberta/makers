
function Container(val){
    let secret = val;
    this.__defineGetter__("secret", function(){ return secret; });
    this.__defineSetter__("secret", function(val){ secret = 45; });
 }
 let test = new Container(35);
 console.log(test.secret)
 test.secret = 45
 console.log(test.secret)
 
 
  



 
 




 

