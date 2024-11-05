function sendCommands(commands) {
  var xhttp = new XMLHttpRequest();
  xhttp.open("GET", "/commands?commands=" + encodeURIComponent(commands), true);
  xhttp.send();
}

$(function () {
  $("#action").submit(function (event) {
      event.preventDefault();
    
      var inputData = $("input[name='commands']").val(); 

      $.ajax({
          type: "GET",
          url: "http://192.168.4.1/commands?commands=" + encodeURIComponent(inputData),
          success: function () {
              alert("Comandos enviados com sucesso!");
          },
          error: function () {
              alert("Erro ao enviar comandos");
          },
      });
  });
});
