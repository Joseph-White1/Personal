function drawGraph() {
  if (localStorage.getItem("tbData") ===
    null) {
    alert("No data exists.");

    $(location).attr("href", "#pageMenu");
  } else {
    setupCanvas();

    var PowConArr = new Array();
    var DateArr = new Array();
    getDataRecords(PowConArr, DateArr);

    var kWhLower = new Array(2);
    var kWhUpper = new Array(2);
    getkWhScale(kWhLower, kWhUpper);

    drawLines(PowConArr, kWhUpper, kWhLower, DateArr)
    labelAxes();
  }
}

function setupCanvas() {

  var c = document.getElementById("GraphCanvas");
  var ctx = c.getContext("2d");

  ctx.fillStyle = "#FFFFFF";
  ctx.fillRect(0, 0, 500, 500);

}

function getDataRecords(PowConArr, DateArr) {
  var tbData = JSON.parse(localStorage.getItem(
    "tbData"));

  tbData.sort(compareDates);

  for (var i = 0; i < tbData.length; i++) {
    var date = new Date(tbData[i].Date);

    /*These methods start at 0, must increment
     * by one to compensate
     */
    var m = date.getMonth() + 1;
    var d = date.getDate();

    //The x-axis label
    DateArr[i] = (m + "/" + d);

    //The point to plot
    PowConArr[i] = parseFloat(tbData[i].KWH);
  }
}

function getkWhScale(kWhLower, kWhUpper)
{
  kWhUpper[0] = kWhUpper[1] = 1000;
  kWhLower[0] = kWhLower[1] = 100;
}


function drawLines(PowConArr, kWhUpper, kWhLower, DateArr) {
  var KWHline = new RGraph.Line("GraphCanvas",
      PowConArr, kWhUpper, kWhLower)
    .Set("labels", DateArr)
    .Set("colors", ["blue", "green", "red"])
    .Set("shadow", true)
    .Set("shadow.offsetx", 1)
    .Set("shadow.offsety", 1)
    .Set("linewidth", 1)
    .Set("numxticks", 6)
    .Set("xaxispos", "bottom")
    .Set("gutter.left", 40)
    .Set("tickmarks", "filledcircle")
    .Set("ticksize", 5)
    .Set("chart.labels.ingraph", [, , ["kWh",
      "blue", "yellow", 1, 80
    ], , ])
    .Set("chart.title", "Power Consumption")
    .Draw();
}

function labelAxes() {
  var c = document.getElementById("GraphCanvas");
  var ctx = c.getContext("2d");
  ctx.font = "11px Georgia";
  ctx.fillStyle = "green";
  ctx.fillText("Date(MM/DD)", 400, 470);
  ctx.rotate(-Math.PI / 2);
  ctx.textAlign = "center";
  ctx.fillText("Kilowatt-hour", -250, 10);
}