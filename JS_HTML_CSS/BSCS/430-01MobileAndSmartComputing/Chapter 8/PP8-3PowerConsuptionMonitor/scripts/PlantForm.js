var SERVER_URL = 'http://127.0.0.1';

$("#btnPlantClear").click(function () {
  clearPlantForm();
});

$("#frmPlantForm").submit(function () { //Event : submitting the form
  savePlantForm();
  return true;
});

function checkPlantForm() { //Check for empty fields in the form
  //for finding current date 
  var d = new Date();
  var month = d.getMonth() + 1;
  var date = d.getDate();
  var year = d.getFullYear();
  var currentDate = year + '/' +
    (('' + month).length < 2 ? '0' : '') +
    month + '/' +
    (('' + date).length < 2 ? '0' : '') + date;

  if (($("#txtPlantID").val() != "") &&
    ($("#datInstDate").val() != "") && 
    ($("#datInstDate").val() <= currentDate))
  {
    return true;
  }
  else
  {
    return false;
  }
}

function savePlantForm() {
  if (checkPlantForm()) {
    var plant = {
      "IdentificationNumber": $("#txtPlantID").val(),
      "InstallDate": $("#datInstDate").val()
    };

    if ($("#btnPlantUpdate").val() == "Create") {
      var plantData = {
        newPlant: plant
      }
      $.post(SERVER_URL + '/saveNewPlant',
        plantData,
        function (data) {
          alert(
            "New Plant Created Successfully!"
          );
          sessionStorage.plant = JSON.stringify(
            plant);
          sessionStorage.password = plant.newPassword;
          $("#btnPlantUpdate").val("Update");
          $.mobile.changePage("#pageMenu");
          window.location.reload();
        }).fail(function (error) {
        alert(error.responseText);
      });
    } else {
      plant.agreedToLegal = JSON.parse(
        sessionStorage.plant).agreedToLegal;
      plant.password = sessionStorage.password;
      $.post(SERVER_URL + '/updatePlant', plant,
        function (data) {
          sessionStorage.plant = JSON.stringify(
            plant);
          sessionStorage.password = plant.newPassword;
        }).fail(function (error) {
        alert(error.responseText);
      }).done(function () {
        $.mobile.changePage("#pageMenu");
        window.location.reload();
      });
    }
  } else {
    alert("Please complete the form properly.");
  }

}

function clearPlantForm() {
  sessionStorage.removeItem("plant");
  alert("The stored data has been removed");
}

function showPlantForm() { //Load the stored values in the form
  if (sessionStorage.plant != null) {
    $("#btnPlantUpdate").val("Update").button(
      "refresh");
    var plant = JSON.parse(sessionStorage.plant);
    $("#txtPlantID").val(plant.IdentificationNumber);
    $("#datInstDate").val(plant.InstallDate);
  } else {
    $("#btnPlantUpdate").val("Create").button(
      "refresh");
  }
}