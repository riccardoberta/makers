function List() {
  this.makeNode = function() { return { data: null, next: null }; };
  this.start = null;
  this.end = null; 
}

List.prototype.add = function(data) {
  if (this.start === null) { this.start = this.makeNode(); this.end = this.start; } 
  else { this.end.next = this.makeNode(); this.end = this.end.next; };
  this.end.data = data;
};

List.prototype.delete = function(data) {
  let current = this.start;
  let previous = this.start;
  while (current !== null) {
    if (data === current.data) {
      if (current === this.start) { this.start = current.next; return; }
      if (current === this.end) this.end = previous;
      previous.next = current.next; return;
    }
    previous = current;
    current = current.next;
  }
};

List.prototype.insertAsFirst = function(d) {
  let temp = List.makeNode();
  temp.next = this.start;
  this.start = temp;
  temp.data = d;
};

List.prototype.insertAfter = function(t, d) {
  let current = this.start;
  while (current !== null) {
    if (current.data === t) {
      let temp = List.makeNode();
      temp.data = d;
      temp.next = current.next;
      if (current === this.end) this.end = temp;
      current.next = temp;
      return;
    }
    current = current.next;
  }
};

List.prototype.item = function(i) {
  let current = this.start;
  while (current !== null) {
    i--;
    if (i === 0) return current;
    current = current.next;
  }
  return null;
};

List.prototype.each = function(f) {
  let current = this.start;
  while (current !== null) {
    f(current);
    current = current.next;
  }
};

var list = new List();
for(var i=1;i<=10;i++){ list.add(i); };
list.each(function(item) { console.log(item.data); });
list.delete(4);
list.each(function(item) { console.log(item.data); });
