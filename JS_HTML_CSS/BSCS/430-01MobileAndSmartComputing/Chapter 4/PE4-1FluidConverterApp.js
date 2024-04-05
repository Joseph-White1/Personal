function setup()
{
  document.getElementById("gallons").onclick = function ()
    {
      setUnits("Litres");
    };
  document.getElementById("litres").onclick = function ()
    {
      setUnits("Gallons");
    };
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