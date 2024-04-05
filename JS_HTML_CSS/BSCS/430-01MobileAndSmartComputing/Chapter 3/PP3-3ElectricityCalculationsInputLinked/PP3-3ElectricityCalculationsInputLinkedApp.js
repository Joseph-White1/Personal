function display()
{
  var power = document.getElementById("power").value;
  var impedance = document.getElementById("impedance").value;

  document.getElementById("powerDisplay").innerHTML = power;
  document.getElementById("impedanceDisplay").innerHTML = impedance;
}