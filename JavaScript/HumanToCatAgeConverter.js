//Human age input
var myAge = 43;

//Designate the number of early years
var earlyYears = 2;

//The first 2 years of cat life is equal to 25 years
earlyYears *= 25;

//Human age minus early years
var laterYears = myAge - 2;

//Human later years in cat years
laterYears *= 4;

//Human age copverted to cat years
var myAgeInCatYears = earlyYears + laterYears

//Human name
var myName = 'Joe'

console.log('My name is ' + myName + '. I am ' + myAge + ' years old in human years, which is ' + myAgeInCatYears + ' years old in cat years.')