function resizeGraph() {
  if ($(window).width() < 700) {
    $("#GraphCanvas").css({
      "width": $(window).width() - 50
    });
    $("#AdviceCanvas").css({
      "width": $(window).width() - 50
    });
  }
}

// Attach event handler for window resizing event
$(window).resize(function () {
  resizeGraph();
});

/*Runs the function to display the user information, history,
 * graph or suggestions, every time their div is shown
 */
$(document).on("pageshow", function () {
  if ($('.ui-page-active').attr('id') ==
    "pageUserInfo") {
    showUserForm();
  } else if ($('.ui-page-active').attr('id') ==
    "pagePlantInfo") {
    showPlantForm();
  } else if ($('.ui-page-active').attr('id') ==
    "pageData") {
    loadUserInformation();
    loadPlantInformation();
    listData();
  } else if ($('.ui-page-active').attr('id') ==
    "pageAdvice") {
    advicePage();
    resizeGraph();
  } else if ($('.ui-page-active').attr('id') ==
    "pageGraph") {
    drawGraph();
    resizeGraph();
  }
});