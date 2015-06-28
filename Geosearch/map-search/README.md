


## How to Run ##

Build the `db` python module for server.

    cd map_db/
    make py
    mv db.so ../server/server/

Run server. Need to install django first.

    cd server/
    python manage.py runserver


## How to test ##

The web address will be http://127.0.0.1:8000.

First input text will control the number of nearest neighbors you need.

Second input text will be used to search by prefix. 

Notice that only keyword in [a-zA-Z0-9]+ will be parsed.
