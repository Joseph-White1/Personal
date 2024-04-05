x = JSON.stringify(home1)
    
var person = 
{
    name: 'Joe',
    age: 43,
    alive: true
};
//console.log(person)

var pizza = {};
    pizza.size = '16"';
    pizza.crust = 'thin';
    pizza.toppings = 'pepperoni, mushrooms, black olives';
    pizza.delivery = false;
    pizza.cost = 20;
//console.log(pizza)

var cup = {};
    cup['ounces'] = 16;
    cup['color'] = 'red';
    cup['plastic'] = true;
//console.log(cup)

var snowman =
{
    isSnow: true,
    color: 'white',
    madeOfSnowballs: 3,
    'first name': 'Frosty'
};
//console.log(snowman.isSnow);
//console.log(snowman.color);
//console.log(snowman.madeOfSnowballs);
//console.log(snowman['first name']);

var house = {};
    house.isOwned = true;
    house.owner = 'John Doe';
    house.squareFootage = 2500;
    house.numberOfAcres = 5;
    house['Year Built'] = 2020;
    house['# of Bedrooms'] = 4;
    house['typeOf'] = 'Ranch';
//console.log(house);

function Home(type, isOwned, squareFootage, bedrooms, acres, yearBuilt)
{
    this.type = type;
    this.isOwned = isOwned;
    this.squareFootage = squareFootage;
    this.bedrooms = bedrooms;
    this.acres = acres;
    this.yearBuilt = yearBuilt;
};
var home1 = new Home('Single Family', true, 2500, 4, 5, 2020);
var home2 = new Home('Farm', true, 3000, 6, 250, 1950);
//console.log(home1);
//console.log(home2);



//alert(x));