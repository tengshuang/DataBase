from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render_to_response

import db

__all__ = [
    'main',
    'search',
]

initialed = False

def main(request):
  global initialed
  if not initialed:
    db.read_json('zipcode-address.json')
    initialed = True
  return render_to_response('main.html')


def search(request):
  #print request.GET['q']
  pois = db.search(float(request.GET['lat']), float(request.GET['lng']),
      request.GET['q'], int(request.GET['num']))
  return HttpResponse(str(pois))
