from django import forms
from .models import Books
import datetime


class BooksForm(forms.ModelForm):
    class Meta:
        model = Books
        fields = ['title', 'author', 'date']
