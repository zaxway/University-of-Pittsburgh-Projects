import re

class Media:
    def __init__(self, title):
        self.title = title;
    def slug(self):
        title = re.sub('[^A-Za-z0-9]+', '', self.title);
        print(self.title);
