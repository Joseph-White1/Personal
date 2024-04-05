var SERVER_URL = 'http://127.0.0.1';

$("#btnUserClear").click(function () {
  clearUserForm();
});

$("#btnUserUpdate").click(function () { //Event : submitting the form
  saveUserForm();
  return true;
});

function checkUserForm() { //Check for empty fields in the form
  //for finding current date 
  var d = new Date();
  var month = d.getMonth() + 1;
  var date = d.getDate();
  var year = d.getFullYear();
  var currentDate = year + '/' +
    (('' + month).length < 2 ? '0' : '') +
    month + '/' +
    (('' + date).length < 2 ? '0' : '') + date;

  if (($("#txtEmail").val() != "") &&
    ($("#txtFirstName").val() != "") &&
    ($("#txtLastName").val() != "") &&
    ($("#datBirthdate").val() != "") && ($(
      "#datBirthdate").val() <= currentDate)) {
    return true;
  } else {
    return false;
  }
}

function saveUserForm() {
  if (checkUserForm()) {
    var user = {
      "Email": $("#txtEmail").val(),
      "FirstName": $("#txtFirstName").val(),
      "LastName": $("#txtLastName").val(),
      "DOB": $("#datBirthdate").val(),
      "NewPassword": $("#changePassword").val()
    };
    if ($("#btnUserUpdate").val() == "Create") {
      var userData = {
        newUser: user
      }
      $.post(SERVER_URL + '/saveNewUser',
        userData,
        function (data) {
          alert(
            "New User Created Successfully!"
          );
          sessionStorage.user = JSON.stringify(
            user);
          sessionStorage.password = user.newPassword;
          $("#btnUserUpdate").val("Update");
          $.mobile.changePage("#pageMenu");
          window.location.reload();
        }).fail(function (error) {
        alert(error.responseText);
      });
    } else {
      user.agreedToLegal = JSON.parse(
        sessionStorage.user).agreedToLegal;
      user.password = sessionStorage.password;
      $.post(SERVER_URL + '/updateUser', user,
        function (data) {
          sessionStorage.user = JSON.stringify(
            user);
          sessionStorage.password = user.newPassword;
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

function clearUserForm() {
  sessionStorage.clear("user");
  alert("The stored data has been removed");
}

function showUserForm() { //Load the stored values in the form
  if (sessionStorage.user != null) {
    $("#btnUserUpdate").val("Update").button(
      "refresh");
    var user = JSON.parse(sessionStorage.user);
    $("#txtEmail").val(user.email);
    $("#txtFirstName").val(user.firstName);
    $("#txtLastName").val(user.lastName);
    $("#datBirthdate").val(user.dateOfBirth);
    $("#changePassword").val(user.newPassword);
  } else {
    $("#btnUserUpdate").val("Create").button(
      "refresh");
  }
}