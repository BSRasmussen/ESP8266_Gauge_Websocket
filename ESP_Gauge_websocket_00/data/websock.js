var websock;
function start() {
  websock = new WebSocket('ws://' + window.location.hostname + ':81/');
  
  websock.onopen = function(evt) {
    console.log('websock open');
    //setInterval(function() {  websock.send('noop\n'); }, 30);
    Gauge.Collection.get('gauge1').setValue(25);
  };
  
  websock.onclose = function(evt) { console.log('websock close'); };
 
  websock.onerror = function(evt) { console.log(evt); };
  
  websock.onmessage = function(evt) {
    console.log(evt);
    console.log(evt.data);
    if (evt.data != ""){
    Gauge.Collection.get('gauge1').setValue(evt.data);}
    else{
	Gauge.Collection.get('gauge1').setValue(50);	
		}
    
    /*var e = document.getElementById('ledstatus');
    if (evt.data === 'ledon\n') {
      e.style.color = 'red';
    }
    else if (evt.data === 'led50\n') {
      e.style.color = 'orange';
    }
    else if (evt.data === 'ledoff\n') {
      e.style.color = 'black';
    }
    else {
      console.log('unknown event', evt.data);
    }*/
  };
}


function buttonclick(e) {
  websock.send("ON");
}

