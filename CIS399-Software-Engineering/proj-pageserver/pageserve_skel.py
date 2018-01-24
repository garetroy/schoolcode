"""
Socket programming in Python
  as an illustration of the basic mechanisms of a web server.

  Based largely on https://docs.python.org/3.4/howto/sockets.html
  This trivial implementation is not robust:  We have omitted decent
  error handling and many other things to keep the illustration as simple
  as possible. 

Garett Roberts
"""

import socket    # Basic TCP/IP communication on the internet
import random    # To pick a port at random, giving us some chance to pick a port not in use
import _thread   # Response computation runs concurrently with main program 
import re

def listen(portnum):
    """
    Create and listen to a server socket.
    Args:
       portnum: Integer in range 1024-65535; temporary use ports
           should be in range 49152-65535.
    Returns:
       A server socket, unless connection fails (e.g., because
       the port is already in use).
    """
    # Internet, streaming socket
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Bind to port and make accessible from anywhere that has our IP address
    serversocket.bind(('', portnum))
    serversocket.listen(1)    # A real server would have multiple listeners
    return serversocket

def serve(sock, func):
    """
    Respond to connections on sock.
    Args:
       sock:  A server socket, already listening on some port.
       func:  a function that takes a client socket and does something with it
    Returns: nothing
    Effects:
        For each connection, func is called on a client socket connected
        to the connected client, running concurrently in its own thread.
    """
    while True:
        print("Attempting to accept a connection on {}".format(sock))
        (clientsocket, address) = sock.accept()
        _thread.start_new_thread(func, (clientsocket,))


CAT = """
     ^ ^
   =(   )=
   """


def respond(sock):
    """
    Respond (only) to GET

    """
    css_file_exists = False
    css_text = ''
    sent = 0
    request = sock.recv(1024)  # We accept only short requests
    request = str(request, encoding='utf-8', errors='strict')
    print("\nRequest was {}\n".format(request))
    html = str(request.splitlines()[0].split(" ")[1][1:])
    try:
      html_text = ''.join([line for line in open(html)])
      if ".css" in html_text:
        css_file_exists = True
        html_lines = html_text.splitlines()
        css_file_name = ''.join([line for line in html_lines if ".css" in line and '<link' in line])
        css_file_name = ''.join([href for href in css_file_name.split(" ") if "href" in href and ".css" in href])
        css_file_name = ''.join(re.findall('"([^"]*)"', css_file_name))
        try:
          css_text = ''.join([line for line in open(css_file_name)])
        except:
          pass
    except:
      html_text = "I don't handle this request"

    parts = request.split()
    if len(parts) > 1 and parts[0] == "GET":
        transmit("HTTP/1.0 200 OK\n\n", sock)
        transmit(html_text, sock)
        if css_file_exists:
          transmit(css_text, sock)
    else:
        transmit("\nI don't handle this request: {}\n".format(request), sock)

    sock.close()

    return

def transmit(msg, sock):
    """It might take several sends to get the whole buffer out"""
    sent = 0
    while sent < len(msg):
        buff = bytes( msg[sent: ], encoding="utf-8")
        sent += sock.send( buff )
    

def main():
    port = random.randint(5000,8000)
    sock = listen(port)
    print("Listening on port {}".format(port))
    print("Socket is {}".format(sock))
    serve(sock, respond)

main()
    
