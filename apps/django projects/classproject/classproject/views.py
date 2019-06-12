from django.http import HttpResponse , HttpRequest

def hello_world(request):
    return HttpResponse("Hello_world ")


