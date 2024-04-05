// Removes all data data from localStorage 
$("#btnClearHistory").click(function () {
  localStorage.removeItem("tbData");
  listData();
  alert("All data has been deleted.");
});

/* The value of the Submit Data button is used
 * to determine which operation should be
 * performed
 */
$("#btnAddData").click(function () {
  /*.button("refresh") function forces jQuery
   * Mobile to refresh the text on the button
   */
  $("#btnSubmitData").val("Add").button(
    "refresh");
});

$("#frmNewDataForm").submit(function () {
  var formOperation = $("#btnSubmitData").val();

  if (formOperation == "Add") {
    addData();
    $.mobile.changePage("#pageData");
  } else if (formOperation == "Edit") {
    editData($("#btnSubmitData").attr(
      "indexToEdit"));
    $.mobile.changePage("#pageData");
    $("#btnSubmitData").removeAttr(
      "indexToEdit");
  }

  /*Must return false, or else submitting form
   * results in reloading the page
   */
  return false;
});

$("#pageNewDataForm").on("pageshow", function () {
  //We need to know if we are editing or adding a data everytime we show this page
  //If we are adding a data we show the form with blank inputs
  var formOperation = $("#btnSubmitData").val();

  if (formOperation == "Add") {
    clearDataForm();
  } else if (formOperation == "Edit") {
    //If we are editing a data we load the stored data in the form
    showDataForm($("#btnSubmitData").attr(
      "indexToEdit"));
  }
});

function loadUserInformation() {
  try {
    var user = JSON.parse(localStorage.getItem(
      "user"));
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
  if (user != null) {
    $("#divUserSection").empty();

    $("#divUserSection").append("User's Name: " +
      user.FirstName + " " + user.LastName +
      "<br>New Password: " + user.NewPassword,
      "<br><a href='#pageUserInfo' data-mini='true' data-role='button' data-icon='edit' data-iconpos='left' data-inline='true' >Edit Profile</a>"
    );
    $('#divUserSection [data-role="button"]').button(); // 'Refresh' the button
  }
}


function loadPlantInformation() {
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
    $("#divPlantSection").empty();

    $("#divPlantSection").append("Plant ID: " +
      plant.IdentificationNumber,
      "<br>Installation Date: " + plant.InstallDate,
      "<br><a href='#pagePlantInfo' data-mini='true' data-role='button' data-icon='edit' data-iconpos='left' data-inline='true' >Edit Plant Info</a>"
    );
    $('#divPlantSection [data-role="button"]').button(); // 'Refresh' the button
  }
}

function clearDataForm() {
  $('#datInputDate').val("");
  $('#txtCkWh').val("");
}

function compareDates(a, b) {
  var x = new Date(a.Date);
  var y = new Date(b.Date);

  if (x > y) {
    return 1;
  } else {
    return -1;
  }
}

function listData() {
  try {
    var tbData = JSON.parse(localStorage.getItem(
      "tbData"));
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

  //Load previous data, if they exist
  if (tbData != null) {
    //Order the data by date
    tbData.sort(compareDates);

    //Initializing the table
    $("#tblData").html(
      "<thead>" +
      "   <tr>" +
      "     <th>Date</th>" +
      "     <th>Power Consumption</th>" +
      "     <th>Edit / Delete</th>" +
      "   </tr>" +
      "</thead>" +
      "<tbody>" +
      "</tbody>"
    );

    //Loop to insert the each data in the table
    for (var i = 0; i < tbData.length; i++) {
      var rec = tbData[i];
      $("#tblData tbody").append("<tr>" +
        "  <td>" + rec.Date + "</td>" +
        "  <td>" + rec.ConPower + "</td>" +
        "  <td><a data-inline='true'  data-mini='true' data-role='button' href='#pageNewDataForm' onclick='callEdit(" +
        i +
        ")' data-icon='edit' data-iconpos='notext'></a>" +
        "  <a data-inline='true'  data-mini='true' data-role='button' href='#' onclick='callDelete(" +
        i +
        ")' data-icon='delete' data-iconpos='notext'></a></td>" +
        "</tr>");
    }

    $('#tblData [data-role="button"]').button(); // 'Refresh' the buttons. Without this the delete/edit buttons wont appear
  } else {
    tbData = []; //If there is no data,set an empty array
    $("#tblData").html("");
  }
  return true;
}

function showDataForm(index) {
  try {
    var tbData = JSON.parse(localStorage.getItem(
      "tbData"));
    var rec = tbData[index];
    $('#datInputDate').val(rec.Date);
    $('#txtCkWh').val(rec.ConPower);
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
}

/* Checks that users have entered all valid info
 * and that the date they have entered is not in
 * the future
 */
function checkDataForm() {
  //for finding current date 
  var d = new Date();
  var month = d.getMonth() + 1;
  var date = d.getDate();
  var currentDate = d.getFullYear() + '/' +
    (('' + month).length < 2 ? '0' : '') +
    month + '/' +
    (('' + date).length < 2 ? '0' : '') + date;

  if (($("#txtCkWh").val() != "") &&
    ($("#datInputDate").val() != "") &&
    ($("#datInputDate").val() <= currentDate)) {
    return true;
  } else {
    return false;
  }
}

function callEdit(index) {
  $("#btnSubmitData").attr("indexToEdit",
    index);
  /*.button("refresh") function forces jQuery
   * Mobile to refresh the text on the button
   */
  $("#btnSubmitData").val("Edit").button(
    "refresh");
}

// Delete the given index and re-display the table
function callDelete(index) {
  deleteData(index);
  listData();
}

function addData() {
  if (checkDataForm()) {
    var data = {
      "Date": $('#datInputDate').val(),
      "ConPower": $('#txtCkWh').val()
    };

    try {
      var tbData = JSON.parse(localStorage.getItem(
        "tbData"));
      if (tbData == null) {
        tbData = [];
      }
      tbData.push(data);
      tbData.sort(compareDates);
      localStorage.setItem("tbData", JSON.stringify(
        tbData));
      alert("Saving Information");
      clearDataForm();
      listData();
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

  return true;
}

function deleteData(index) {
  try {
    var tbData = JSON.parse(localStorage.getItem(
      "tbData"));

    tbData.splice(index, 1);

    if (tbData.length == 0) {
      /* No items left in data, remove entire 
       * array from localStorage
       */
      localStorage.removeItem("tbData");
    } else {
      localStorage.setItem("tbData", JSON.stringify(
        tbData));
    }
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
}

function editData(index) {
  if (checkDataForm()) {
    try {
      var tbData = JSON.parse(localStorage.getItem(
        "tbData"));
      tbData[index] = {
        "Date": $('#datInputDate').val(),
        "ConPower": $('#txtCkWh').val()
      }; //Alter the selected item in the array
      tbData.sort(compareDates);
      localStorage.setItem("tbData", JSON.stringify(
        tbData)); //Saving array to local storage
      alert("Saving Information");
      clearDataForm();
      listData();
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