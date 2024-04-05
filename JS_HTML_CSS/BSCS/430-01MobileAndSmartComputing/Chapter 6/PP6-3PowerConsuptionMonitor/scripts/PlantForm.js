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

    try {
      localStorage.setItem("plant", JSON.stringify(
        plant));
      alert("Saving Information");

      $.mobile.changePage("#pageMenu");
      window.location.reload();
    } catch (e) {
      /* Google browsers use different error 
       * constant
       */
      if (window.navigator.vendor ===
        "Google Inc.") {
        if (e == DOMException.QUOTA_EXCEEDED_ERR) {
          alert(
            "Error: Local Storage limit exceeds."
          );
        }
      } else if (e == QUOTA_EXCEEDED_ERR) {
        alert("Error: Saving to local storage.");
      }

      console.log(e);
    }
  } else {
    alert("Please complete the form properly.");
  }

}

function clearPlantForm() {
  localStorage.removeItem("plant");
  alert("The stored data have been removed");
}

function showPlantForm() { //Load the stored values in the form
  try {
    var plant = JSON.parse(localStorage.getItem(
      "plant"));
  } catch (e) {
    /* Google browsers use different error 
     * constant
     */
    if (window.navigator.vendor ===
      "Google Inc.") {
      if (e == DOMException.QUOTA_EXCEEDED_ERR) {
        alert(
          "Error: Local Storage limit exceeds."
        );
      }
    } else if (e == QUOTA_EXCEEDED_ERR) {
      alert("Error: Saving to local storage.");
    }

    console.log(e);
  }

  if (plant != null) {
    $("#txtPlantID").val(plant.IdentificationNumber);
    $("#datInstDate").val(plant.InstallDate);
  }
}