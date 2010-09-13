  // Nasty Globals (because all globals are nasty)
  var server = 'http://localhost:9020';
  var room = 'Pirate Chat';

  // A nice helper function for updating the chat display
  var update_chat = function() {
    res = "/chat";
    params = {"room" : room };
    $.get(server + res, params, function(resp){
      $('#wysiwyg')
        .html(resp)
        .attr({ scrollTop: $("#wysiwyg").attr("scrollHeight") })
      ;
    });
  };

  // Define the Application's Routes
  var app = $.sammy(function() {
    this.get('#/', function() {
      $('#main').text('Welcome!');
    });

    this.get('#/room/:room', function() {
      room = params['room'];
      update_chat();
    });

    this.post('#/chat', function(ev) {
      room = $('form').find('[name=room]').val();
      name = $('form').find('[name=name]').val();
      msg = $('form').find('[name=msg]').val();
      $('form').find('[name=msg]').val('');

      res = '/CHAT';
      params = 'name=' + name + ';line=' + msg + ';room=' + room;
      $.get(server + res + '?' + params, undefined, function(resp){
        $('#wysiwyg')
          .html(resp)
          .attr({ scrollTop: $("#wysiwyg").attr("scrollHeight") })
        ;
      });
      return false;
    });
  });


  // Init the program
  $(document).ready(function() {
    app.run();
    room = $('form').find('[name=room]').val();
    setInterval(update_chat, 2000);
  }); 
