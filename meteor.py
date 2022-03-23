from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
from selenium import webdriver
import datetime
from selenium.common.exceptions import ElementClickInterceptedException 
import colorama
from selenium.common.exceptions import StaleElementReferenceException
import json
import urllib.parse
import pandas as pd

#parse url as root and subdomain
url_root = 'https://meteor.today'
vs_new = '/board/vschool/new'

#enable log capture
caps = DesiredCapabilities.CHROME
caps['goog:loggingPrefs'] = {'performance': 'ALL'}

browser = webdriver.Chrome(desired_capabilities=caps)
browser.implicitly_wait(10)
browser.get(url_root + vs_new)

#prompt user that the crawler is doing good
print(f"{datetime.datetime.now()} --------> Start loading all the content from {url_root}{vs_new}")

#find the load more bottom and then click it
counter = {'ElementClickInterceptedException': 0, 'StaleElementReferenceException': 0}
while True:
    loading_more = browser.find_elements_by_class_name('bottom')
    try:
        loading_more[0].click()
    except ElementClickInterceptedException: #too quick to loading content
        counter['ElementClickInterceptedException'] += 1
        print(f"selenium.common.exceptions ElementClickInterceptedException {colorama.Fore.RED}{colorama.Back.WHITE}{counter['ElementClickInterceptedException']}{colorama.Fore.RESET}{colorama.Back.RESET} times.\r" , end='')
    except StaleElementReferenceException: #too quick to loading content
        counter['StaleElementReferenceException'] += 1
        print(f"selenium.common.exceptions StaleElementReferenceException {colorama.Fore.RED}{colorama.Back.WHITE}{counter['StaleElementReferenceException']}{colorama.Fore.RESET}{colorama.Back.RESET} times.\r", end='')
    except IndexError: #already exhausted all content
        break
print()

article = []
for traffic in browser.get_log('performance'):
    try:
        #extract request ID and url for further use
        params = json.loads(traffic['message'])['message']['params']
        requestId = params['requestId']
        url = params['response']['url']

        #traffic filter
        if "new_article" in url:
            #get response payload by ID
            payload = browser.execute_cdp_cmd("Network.getResponseBody", {"requestId": requestId})['body']
            
            #unquote the payload
            decoded = urllib.parse.unquote(json.loads(payload)['result'])

            #parse again
            parsed_json = json.loads(decoded)

            #extract needed information
            for topic in parsed_json:
                article.append({ 
                    'title': topic['title'],
                    'like': topic['starLength'],
                    'datetime': topic['createdAt']
                    })
    except KeyError: #ignore some traffic we do not interest in
        pass
browser.quit()

print(f"{datetime.datetime.now()} --------> Crawler has finished successfully.")

#convert list into dataframe
df = pd.DataFrame(article)

#convert dataframe into CSV file
df.to_csv('meteor.csv', index=True, encoding='utf8')
