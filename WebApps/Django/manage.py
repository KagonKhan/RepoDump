#!/usr/bin/env python
"""
Command-line utility for administrative tasks.

# For more information about this file, visit
# https://docs.djangoproject.com/en/2.1/ref/django-admin/
"""

import os
import sys

if __name__ == '__main__':
    os.environ.setdefault( 'DJANGO_SETTINGS_MODULE', 'Django_playground.settings')

    from django.core.management import execute_from_command_line
  
    execute_from_command_line(sys.argv)
