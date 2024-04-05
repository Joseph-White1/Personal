function advicePage() {
  if (localStorage.getItem("tbData") ===
    null) {
    alert("No Data exists.");

    $(location).attr("href", "#pageMenu");
  } else {

    var Avg = new Number;
    findAverage(Avg);

    var tbData = JSON.parse(localStorage.getItem("tbData"));
    tbData.sort(compareDates);
    var i = tbData.length - 1;
    var KWH = tbData[i].KWH;

    var c = document.getElementById("AdviceCanvas");
    var ctx = c.getContext("2d");
    ctx.fillStyle = "#c0c0c0";
    ctx.fillRect(0, 0, 500, 500);
    ctx.font = "22px Arial";
    drawAdviceCanvas(ctx, Avg, KWH);
  }
}

function getDataRecords(recArr)
{
  var tbData = JSON.parse(localStorage.getItem("tbData"));
  tbRecords.sort(compareDates);

  for (var i = 0; i < tbData.length; i++)
  {
    recArr[i] = parseFloat(tbData[i].KWH);
  }
}

function findAverage(Avg)
{
  var AvArr = new Array();
  getDataRecords(recArr);
  TOTAL = 0;
  length = AvArr.length;
  for(var i = AvArr.length; i > 0; i--)
  {
    TOTAL += AvArr[i];
  }
  Avg = TOTAL / AvArr.length;
}

function drawAdviceCanvas(ctx, Avg, KWH) {
  ctx.font = "22px Arial";
  ctx.fillStyle = "black";
  ctx.fillText("Your current power consupmtion is: " + KWH, 25, 400);
  ctx.fillText("The average for the past six months is: " + Avg, 25, 400);
  levelWrite(ctx, KWH);
  levelMeter(ctx, KWH);
}

//For deciding what to write for given values of KWH level A
function levelWrite(ctx, KWH) {
  if (KWH < Avg - 100) {
    writeAdvice(ctx, "green");
  } else if (KWH > Avg + 100) {
    writeAdvice(ctx, "red");
  } else {
    writeAdvice(ctx, "yellow");
  }
}

function writeAdvice(ctx, level) {
  var adviceLine = "";

  if (level == "red") {
    adviceLine =
      "Power consumption level is above average";
  } else if (level == "yellow") {
    adviceLine =
      "Power consumption level is average";
  } else if (level = "green") {
    adviceLine =
      "Power consumption level is below average";
  }
  ctx.fillText("Your Kilowatt-hour usage is " + level, 25, 400);
  ctx.fillText(adviceLine, 25, 400);
}

function levelMeter(ctx, KWH) {
  if (KWH < 1000) {
    var cg = new RGraph.CornerGauge(
        "AdviceCanvas", 0, 1000, KWH)
      .Set("chart.colors.ranges", [
        [KWH > Avg + 100, 999.99, "red"],
        [KWH < Avg - 100, KWH > Avg + 100, "yellow"],
        [0, KWH < Avg - 100, "green"]
      ]);
  } else {
    var cg = new RGraph.CornerGauge(
        "AdviceCanvas", 1000, KWH, KWH)
      .Set("chart.colors.ranges", [
        [1000, KWH, "red"]
      ]);
  }
  drawMeter(cg);
}

// Meter properties
function drawMeter(g) {
  g.Set("chart.value.text.units.post", " kWh")
    .Set("chart.value.text.boxed", false)
    .Set("chart.value.text.size", 14)
    .Set("chart.value.text.font", "Verdana")
    .Set("chart.value.text.bold", true)
    .Set("chart.value.text.decimals", 2)
    .Set("chart.shadow.offsetx", 5)
    .Set("chart.shadow.offsety", 5)
    .Set("chart.scale.decimals", 2)
    .Set("chart.title", "KWH LEVEL")
    .Set("chart.radius", 250)
    .Set("chart.centerx", 50)
    .Set("chart.centery", 250)
    .Draw();
}