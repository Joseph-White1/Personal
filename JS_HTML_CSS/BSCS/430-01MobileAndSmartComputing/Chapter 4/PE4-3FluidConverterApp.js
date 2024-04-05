function initialize()
{
  var userInput = document.getElementById("quantity");
  userInput.addEventListener("blur", validateInput);
}

function setUnits(unit)
{
  var label = document.getElementById("label");
  label.innerHTML = unit;
}

function convert()
{
  var litresButton = document.getElementById("litres");
  var quantity = document.getElementById("quantity");

  if (litresButton.checked)
  {
    convertToLitres(quantity.value);
  }
  else
  {
    convertToGallons(quantity.value);
  }
}

function convertToLitres(quantityInGallons)
{
  var litresQuantity = (quantityInGallons) * 3.785411784 ;
  document.getElementById("answer").innerHTML = quantityInGallons +
    "Gallons converts to " +
    litresQuantity.toFixed(2) +
    "litres";
}

function convertToGallons(quantityInLitres)
{
  var gallonsQuantity = quantityInLitres / 3.785411784;
  document.getElementById("answer").innerHTML = quantityInLitres +
    "Litres converts to " +
    gallonsQuantity.toFixed(2) +
    "gallons";
}

function validateInput()
{
  if (document.getElementById("litres").checked)
  {
    var gallons = document.getElementById("quantity").value;
    if (gallons < 1 || gallons > 1000)
    {
      alert ('Gallons entered must be between 1 and 1000');
      gallons = "";
    }
  }
  else
  {
    var litres = document.getElementById("quantity").value;
    if (litres < 1 || litres > 4000)
    {
      alert ('Litres entered must be between 1 and 4000');
      litres = "";
    }
  }
}