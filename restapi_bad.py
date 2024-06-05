import json
from flask import Flask, jsonify, request
app = Flask(__name__)

response_pv = \
 { 
   "estimated_actuals": [
     {
       "pv_estimate": 2.7698,
       "period_end": "2024-06-01T09:00:00.0000000Z",
       "period": "PT30M"
     },
     {
       "pv_estimate": 2.7155,
       "period_end": "2024-06-01T08:30:00.0000000Z",
       "period": "PT30M"
     },
     {
       "pv_estimate": 2.6189,
       "period_end": "2024-06-01T08:00:00.0000000Z",
       "period": "PT30M"
     }
  ]
}


# /rooftop_sites/e5cc-f38e-7730-805d/estimated_actuals?api_key=u70RlALYTh-bWi9lDsuRKxWWi3jQApLz&format=json&hours=1
@app.route('/rooftop_sites/e5cc-f38e-7730-805d/estimated_actuals', methods=['GET'])
def get_pv():
 return jsonify(response_pv)


if __name__ == '__main__':
   app.run(debug=True, host='0.0.0.0', port=10)
