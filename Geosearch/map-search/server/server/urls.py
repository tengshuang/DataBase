from django.conf.urls import patterns
from views import main, search


urlpatterns = patterns('',
    (r'^$', main),
    (r'^search/$', search),

)
