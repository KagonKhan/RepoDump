from django.shortcuts import render, redirect, get_object_or_404
from django.http import HttpResponse
from .models import News
from .forms import NewsForm
from django.utils import timezone                                                                   
from django.contrib.auth.decorators import login_required


# Create your views here.

def index(request):
    news = News.objects.order_by('-create_time')
    context = {'news': news}
    return render(request, 'news/index.html', context)

@login_required(login_url='/login/')
def add(request):
    if ( request.method == 'POST' ):
        news = NewsForm(request.POST)

        if( news.is_valid() ):
            news = news.save( commit=False )
            news.create_time = timezone.now()
            news.last_edit_time = timezone.now()
            news.save()
            return redirect('view_news')
        else:
            context = { 'form': news }
            return render(request, 'news/add.html', context)
    else:
        news = NewsForm()
        context = { 'form': news }
        return render(request, 'news/add.html', context)


def get(request, id):
    news = get_object_or_404(News, id=id)
    context = { 'news': news }
    return render(request, 'news/view.html', context)



@login_required(login_url='/login/')
def edit(request, id):
    news = get_object_or_404(News, id=id)
    context = { 'news': news }
    return render(request, 'news/edit.html', context)
@login_required(login_url='/login/')
def update(request, id):
    updatenews = get_object_or_404(News, id=id)
    updatenews.last_edit_time = timezone.now()
    news = NewsForm(request.POST, instance=updatenews)
    if( news.is_valid() ):
        news.save()

    context = { 'news': news }
    return redirect(index)