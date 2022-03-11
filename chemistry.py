from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.common.exceptions import ElementClickInterceptedException 
from bs4 import BeautifulSoup
import pandas as pd
import time

#parse url as root and subdomain
url_root = 'https://meteor.today'
vs_new = '/board/vschool/new'

option = Options()
#option.add_argument('--headless')

#connect
browser = webdriver.Chrome(options=option)
browser.implicitly_wait(10)
browser.get(url_root + vs_new)

#find the load more bottom and then click it
while True:
    loading_more = browser.find_elements_by_class_name('bottom')
    try:
        loading_more[0].click()
        time.sleep(.15) #wait for page loading
    except ElementClickInterceptedException: #too quick to loading content
        print("exception")
    except IndexError: #already exhausted all content
        break

#get whole html codes by body tag
#explictily using html parser to suppress warning messages
soup = BeautifulSoup(browser.find_element_by_tag_name('body').get_attribute('innerHTML'), features='html.parser')

tags = soup.find_all('a', class_='item ng-scope')

article = []
for tag in tags:
    if tag.find('div'):
        #strip() = lstrip() + rstrip()
        title = tag.find('div', 'header ng-binding').text.strip() 
        like = tag.find('div').text
        #hypertext link to each page
        href = tag['href']
        article.append({'title': title, "like": like, "href": href})

for a in article:
    browser.get(url_root + a[href])
    innersoup = BeautifulSoup(browser.find_element_by_tag_name('body').get_attribute('innerHTML'), features='html.parser')
    tmp = innerHTML.find_all('div', class_='sub header')
    print(tmp)

#shut selenium down as soon as possible to save resource
browser.quit()

df = pd.DataFrame(article)
df = df[ ~ df['title'].str.contains('#公告')]
df = df[ ~ df['title'].str.contains('#抽獎')]
df = df[ ~ df['title'].str.contains('聯賽足球')]
df.to_csv('meteor.csv', index=True, encoding='utf8')
