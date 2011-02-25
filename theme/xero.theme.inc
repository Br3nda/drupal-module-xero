<?php

/**
 * @file
 * Xero theme preprocess callbacks
 */


/**
 * Theme Addresses properly
 * @param addresses an array of addresses
 * @return HTML formatted string
 */
function theme_xero_addresses($addresses) {
  $o = '';
  foreach ($addresses as $address) {
    $o .= '<div class="xero-address">';
    for ($i = 1; $i < 5; $i++) {
      if (isset($address['AddressLine'.$i]) && !empty($address['AddressLine'.$i])) {
        $o .= '<div class="xero-address-line">' . check_plain($address['AddressLine'.$i]) . '</div>';
      }
    }
    $o .= '<div class="xero-address-line">' . check_plain($address['City']) . ', ' . check_plain($address['Region']) . ' ' . check_plain($address['PostalCode']) . ' ' . check_plain($address['Country']) . '</div>';
    $o .= "</div>\n";
  }

  return $o;
}

/**
 * Theme Xero Line Items properly.
 * @param $items an array of line items
 * @param $subtotal the subtotal of the invoice
 * @param $tax the total tax of the invoice
 * @param $total the grand total of the invoice
 * @return HTML formatted string
 */
function theme_xero_lineitems($items, $subtotal, $tax, $total) {
  $header = array(t('Description'), t('Quantity'), t('Unit Price'), t('Tax'), t('Amount'), t('Account'), t('Category'));
  $rows = array();

  foreach ($items as $item) {
    $row = array();
    $categories = '';

    $row[] = check_plain($item['Description']);
    $row[] = $item['Quantity'];
    $row[] = $item['UnitAmount'];
    $row[] = $item['TaxAmount'];
    $row[] = $item['LineAmount'];
    $row[] = $item['AccountCode'];

    if (!empty($item['Tracking'])) {
      foreach ($item['Tracking']['TrackingCategory'] as $category) {
        $categories .= check_plain($category['Option']);
      }
      $row[] = $categories;
    }

    $rows[] = $row;
  }

  $rows[] = array('', '', '', $tax, $subtotal);
  $rows[] = array('', '', '', '', '<b>' . $total . '</b>');

  return theme('table', $header, $rows, array('class' => 'xero-lineitems'), t('Line Items'));
}


/**
 * Xero Contact Preprocess Callback
 * @param &$variables Variables to pass back and forth.
 */
function template_preprocess_xero_contact(&$variables) {
  $contact = $variables['contact'] = $variables[0];
  unset($variables[0]);

  $variables['contactid'] = $contact['ContactID'];
  $variables['company'] = check_plain($contact['Name']);
  $variables['contact_name'] = (isset($contact['FirstName'])) ? $contact['FirstName'] : '';
  $variables['contact_name'] .= (isset($contact['LastName'])) ? ' ' . $contact['LastName'] : '';
  $variables['contact_name'] = check_plain($variables['contact_name']);
  $variables['mail'] = (isset($contact['EmailAddress'])) ? $contact['EmailAddress'] : '';
  $variables['status'] = $contact['ContactStatus'];
  $update = new DateTime($contact['UpdatedDateUTC']);
  $variables['updated'] = $update->format('U');
 
  if ($contact['IsSupplier'] == 'true') {
    $variables['type'] = 'supplier';
  }
  elseif ($contact['IsCustomer'] == 'true') {
    $variables['type'] = 'customer';
  }
  else {
    $variables['type'] = '';
  }

  $variables['addresses'] = array();
  if (!empty($contact['Addresses']['Address'])) {
    $variables['addresses'] = $contact['Addresses']['Address'];
  }

  $variables['phones'] = array();
  if (!empty($contact['Phones'])) {
    foreach ($contact['Phones']['Phone'] as $phone) {
      $type = '<span class="xero-phone-type">' . ucwords(strtolower($phone['PhoneType'])) . ':</span>';
      if (empty($phone['PhoneCountryCode']) || empty($phone['PhoneAreaCode']) || empty($phone['PhoneNumber'])) {
        $number = '';
      }
      else {
        $number = check_plain($phone['PhoneCountryCode']) . '-' . check_plain($phone['PhoneAreaCode']) . '-' . check_plain($phone['PhoneNumber']);
      }
      $variables['phones'][] = $type . ' ' . $number;
    }
  }

  $variables['groups'] = array();
  if (!empty($contact['ContactGroups'])) {
    foreach ($contact['ContactGroups']['ContactGroup'] as $group) {
      $variables['groups'][] = check_plain($group);
    }
  }
}

/**
 * Xero Invoice Preprocess callback
 * @param &$variables Variables passed back and forth.
 */
function template_preprocess_xero_invoice(&$variables) {
  $invoice = $variables['invoice'] = $variables[0];
  unset($variables[0]);

  $variables['currency'] = (isset($invoice['CurrencyCode'])) ? $invoice['CurrencyCode'] : ''; //USD, NZD

  $variables['type'] = strtolower($invoice['Type']);
  $variables['status'] = ucwords(strtolower($invoice['Status']));
  $variables['invoiceid'] = $invoice['InvoiceID'];
  $variables['number'] = check_plain($invoice['InvoiceNumber']);
  $variables['name'] = check_plain($invoice['Contact']['Name']);
  $variables['contactid'] = $invoice['Contact']['ContactID'];

  $date = new DateTime($invoice['Date']);
  $variables['date'] = $date->format('U');
  $duedate = new DateTime($invoice['DueDate']);
  $variables['duedate'] = $duedate->format('U');

  $variables['total'] = (isset($invoice['Total'])) ? $invoice['Total'] : '0.00';
  $variables['paid'] = (isset($invoice['AmountPaid'])) ? $invoice['AmountPaid'] : '0.00';
  $variables['due'] = (isset($invoice['AmountDue'])) ? $invoice['AmountDue'] : '0.00';
  $variables['credited'] = (isset($invoice['AmountCredited'])) ? $invoice['AmountCredited'] : '0.00';
  $variables['lineamounttypes'] = $invoice['LineAmountTypes'];

  $variables['lineitems'] = array();
  if (!empty($invoice['LineItems']['LineItem'])) {
    $variables['lineitems'] = $invoice['LineItems']['LineItem'];
  }

  $variables['payments'] = '';
  if (!empty($invoice['Payments']['Payment'])) {
    $header = array(t('Date'), t('Amount'));
    $rows = array();

    foreach ($invoice['Payments']['Payment'] as $payment) {
      $row = array();

      $date = new DateTime($payment['Date']);
      $row[] = format_date($date->format('U'), 'short');
      $row[] = $payment['Amount'];

      $rows[] = $row;
    }

    $variables['payments'] = theme('table', $header, $rows, array('class' => 'xero-payments'), t('Payments'));
  }

}

/**
 * Xero Credit Note Preprocess callback
 * @param &$variables Variables to pass back and forth.
 */
function template_preprocess_xero_creditnote(&$variables) {
  $cn = $variables['creditnote'] = $variables[0];
  unset($variables[0]);

  $variables['currency'] = (isset($cn['CurrencyCode'])) ? $cn['CurrencyCode'] : ''; //USD, NZD

  $variables['type'] = strtolower(substr($cn['CreditNoteType'], 6));
  $variables['status'] = ucwords(strtolower($cn['Status']));
  $variables['number'] = check_plain($cn['CreditNoteNumber']);
  $variables['creditnotid'] = $cn['CreditNoteID'];
  $variables['name'] = check_plain($cn['Contact']['Name']);
  $variables['contactid'] = $cn['Contact']['ContactID'];
  $date = new DateTime($cn['Date']);
  $due = new DateTime($cn['DueDate']);
  $updated = new DateTime($cn['UpdatedDateUTC']);
  $variables['date'] = $date->format('U');
  $variables['duedate'] = $due->format('U');
  $variables['updated'] = $updated->format('U');

  if (isset($cn['FullyPaidOnDate'])) {
    $paidon = new DateTime($cn['FullyPaidOnDate']);
    $variables['paidon'] = $paidon->format('U');
  }
  else {
    $variables['paidon'] = '';
  }

  $varaibles['lineitems'] = array();
  if (!empty($cn['LineItems']['LineItem'])) {
    $variables['lineitems'] = $cn['LineItems']['LineItem'];
  }
}
