//Kelvin temp input
var kelvinTemp = 301;

//Celcuis converted from Kelvin
var celcuisTemp = kelvinTemp - 273.15;

//Fahrenheit converted from Celcuis
var fahrenheitTemp = celcuisTemp * (9/5) + 32;

//Floor Farehnheit temp (other math functions are .ceil & .round)
fahrenheitTemp = Math.floor(fahrenheitTemp);

//String concatenation output
console.log('The temperature is ' + fahrenheitTemp + ' degrees Fahrenheit.')