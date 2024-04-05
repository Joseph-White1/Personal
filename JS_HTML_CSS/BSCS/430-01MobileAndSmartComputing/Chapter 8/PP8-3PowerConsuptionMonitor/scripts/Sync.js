var SERVER_URL = "http://127.0.0.1";

// Updates data on the server to match the data on the device
$("#btnUpload").click(function () {
  if (sessionStorage.tbData) {
    var requestBody = {
      email: JSON.parse(sessionStorage.user)
        .email,
      password: sessionStorage.password,
      newData: JSON.parse(sessionStorage
        .tbData)
    };
    $.post(SERVER_URL + "/syncData",
      requestBody,
      function (data) {
        alert(
          "Data uploaded successfully!"
        );
      }).fail(function (error) {
      alert(error.responseText);
    });
  } else {
    alert("No data to save!");
  }
});

// Downloads data from the server, only updating data that are
// not already on the device (determined by the date of the record)
$("#btnDownload").click(function () {
  var credentials = {
    email: JSON.parse(sessionStorage.user).email,
    password: sessionStorage.password
  };
  $.post(SERVER_URL + '/getData',
    credentials,
    function (data) {
      alert(
        'Data downloaded successfully!'
      );
      var tbData = [];
      if (sessionStorage.tbData) {
        tbData = JSON.parse(
          sessionStorage.tbData);
      }
      for (var i = 0; i < data.length; i++) {
        var exists = false;
        for (var j = 0; j < tbData.length; j++) {
          if (tbData[j].date == data[i].date) {
            exists = true;
          }
        }
        if (!exists) {
          tbData.push(data[i]);
        }
      }
      sessionStorage.tbData = JSON.stringify(
        tbData);
    }).fail(function (error) {
    alert(error.responseText);
  })
});

// Downloads data from the server and overwrites all data
// currently on the device
$("#btnDownloadOverwrite").click(function () {
  var credentials = {
    email: JSON.parse(sessionStorage.user).email,
    password: sessionStorage.password
  };
  $.post(SERVER_URL + '/getData',
    credentials,
    function (data) {
      alert(
        'Data downloaded successfully!'
      );
      sessionStorage.tbData = JSON.stringify(
        data);
    }).fail(function (error) {
    alert(error.responseText);
  })
});