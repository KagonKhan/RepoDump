from django.shortcuts import render, redirect, get_object_or_404
from django.http import HttpResponse
from .models import Books
from .forms import BooksForm
from django.utils import timezone                                                                   
from django.contrib.auth.decorators import login_required


# Create your views here.

def index(request):
    books = Books.objects.order_by('-title')
    context = {'books': books}
    return render(request, 'books/index.html', context)

@login_required(login_url='/login/')
def add(request):
    if ( request.method == 'POST' ):
        book = BooksForm(request.POST)

        if( book.is_valid() ):
            book.save()
            return redirect('view_books')
        else:
            context = { 'form': book }
            return render(request, 'books/add.html', context)
    else:
        book = BooksForm()
        context = { 'form': book }
        return render(request, 'books/add.html', context)


def get(request, id):
    book = get_object_or_404(Books, id=id)
    context = { 'book': book }
    return render(request, 'books/view.html', context)



@login_required(login_url='/login/')
def edit(request, id):
    book = get_object_or_404(Books, id=id)
    context = { 'book': book }
    return render(request, 'books/edit.html', context)

@login_required(login_url='/login/')
def update(request, id):
    updatebook = get_object_or_404(Books, id=id)
    book = BooksForm(request.POST, instance=updatebook)
    if( book.is_valid() ):
        book.save()

    return redirect(index)


@login_required(login_url='/login/')
def delete(request, id):
    Books.objects.get(id=id).delete()

    return redirect(index)