x = JSON.stringify(shoppingList);

var shoppingList = ['apples', 'pizza', 'chicken', 'mushrooms', 'oranges', 'beef'];

shoppingList.unshift('crackers');
shoppingList.push('grapes');
shoppingList.push('siracha', 'popcorn');
shoppingList.unshift('lemonade', 'orange juice');
shoppingList.shift();
shoppingList.pop();

shoppingList;
alert(x);
alert(shoppingList.length);