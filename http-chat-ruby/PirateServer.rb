#!/usr/bin/env ruby

require 'rubygems'
require 'eventmachine'
require 'evma_httpserver'
require 'cgi'
require 'active_support'

PUBLIC_DIR = './public/'
INDEX = PUBLIC_DIR + 'index.html'
CHAT_CLIENT = PUBLIC_DIR + 'chatroom.html'
NOT_FOUND = PUBLIC_DIR + '404.html'
UNPROCESSABLE_ENTITY = PUBLIC_DIR + '422.html'

class ChatRequest  < EventMachine::Connection
  # HTTPServer handles preprocessing the HTTP headers and such
  include EventMachine::HttpServer

  # Setup rooms
  def initialize
    @@rooms = {} unless defined?(@@rooms)
  end
 
  def process_http_request
    resp = EventMachine::DelegatedHttpResponse.new( self )

    # Callback 
    callback = proc do |res|
      resp.send_response
    end
 
    # Handler
    handler = proc do
      @content = ''
      @type = 'text/html'
      route_request
      #resp.headers['Content-Type'] = @type
      resp.status = @status
      resp.content = @content
    end

    # defer starts a new Ruby (user-level, not os-level) thread
    # By default will allow 20 Ruby threads
    EM.defer(handler, callback)
  end

  # Do Routing
  def route_request
    puts @http_request_uri + '?' + @http_query_string.to_s
    @status = 200
    # Ignoring the http verb and assuming GET
    case @http_request_uri
      when /^\/$/ then index
      when /^\/CHAT$/ then chat
      when /^\/chat$/ then gossip
      else
        find_file
    end
  end

  # Routes
  def index
    @content = open(INDEX).read
  end

  def client
    @content = open(CHAT_CLIENT).read
  end

  def chat
    if @http_query_string.nil?
      return client
    end

    client_name, client_line, room_name = parse_params
    if client_name.nil? || client_line.nil?
      return bad_request
    end

    room = find_or_create_room(room_name)
    clients = room[:clients] ||= {}
    lines = room[:lines] ||= []

    # Trim to the last 100 lines
    while lines.size >= 100
      lines.shift
    end
    time = Time.now
    lines << "(#{time.strftime("%H:%M:%S")}) #{client_name}: #{client_line}"

    # Find or create the client
    client = clients[client_name] ||= {}
    client[:name] ||= client_name
    client[:last_seen] ||= time

    # Make client leave from all rooms if not recently seen
    if client[:last_seen] < 30.minutes.ago
      @@rooms.each do |rkey,rhash|
        rkey[:clients].reject! do |ukey,uhash|
          ukey == client[:name]
        end
      end
    end

    gossip
  end

  # Create the text of the entire chat
  def gossip
    puts "In gossip"
    client_name, client_line, room_name = parse_params
    room = find_or_create_room(room_name)
    lines = room[:lines] || ["Welcome"]
    lines.inspect
    @content = "<p>Room: #{room_name}"
    lines.each do |line|
      @content += '<br/>' + line
    end
    @content += "</p>"
    puts "Out gossip"
  end

  def bad_request
    @status = 422
    @content = open(UNPROCESSABLE_ENTITY).read
  end

  def find_file
    unless File.exists?(PUBLIC_DIR + @http_request_uri)
      return not_found
    end
    @content = open(PUBLIC_DIR + @http_request_uri).read
  end

  def not_found
    @status = 404
    @content = open(NOT_FOUND).read
  end


  # Utility Functions
  def parse_params
    @http_query_string = CGI::unescape(@http_query_string)
    if match = /.*name=([^\;]*)/.match(@http_query_string)
      client_name = match[1]
    end
    if match = /.*line=([^\;]*)/.match(@http_query_string)
      client_line = match[1]
    end
    room_name = 'default'
    if match = /.*room=([^\;]*)/.match(@http_query_string)
      room_name = match[1]
    end
    client_name ||= nil
    client_line ||= nil
    room_name ||= nil
    return [client_name, client_line, room_name]
  end

  def find_or_create_room(room_name)
    @@rooms[room_name] ||= {}
    @@rooms[room_name]
  end
end
 
EventMachine::run {
  EventMachine.epoll
  # Uses TCP by default. UDP must be specified
  EventMachine::start_server("0.0.0.0", 9020, ChatRequest)
  puts "Listening..."
}
