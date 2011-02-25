<?php
/**
 * @file
 */


/**
 * Administrative settings form callback
 */
function xero_admin_settings() {
  $form = array();

  $form['xero_consumer_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Xero Consumer Key'),
    '#description' => t('Provide the consumer key for your private application on xero.'),
    '#default_value' => variable_get('xero_consumer_key', ''),
  );

  $form['xero_consumer_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Xero Consumer Secret'),
    '#description' => t('Provide the consumer secret for your private application on xero.'),
    '#default_value' => variable_get('xero_consumer_secret', ''),
  );

  $form['xero_cert_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Xero Certificate Path'),
    '#description' => t('Provide the full path and file name to your Xero certificate.'),
    '#default_value' => variable_get('xero_cert_path', ''),
  );

  $form['xero_key_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Xero Key Path'),
    '#description' => t('Provide the full path and file name to your Xero certificate private key.'),
    '#default_value' => variable_get('xero_key_path', ''),
  );

  return system_settings_form($form);
}

/**
 * Xero Autocomplete Contacts page callback
 * @param $string the string to search
 */
function xero_autocomplete_contacts($string = '') {
  $contacts = xero_get_cache('Contacts');
  $matches = array();

  foreach ($contacts['Contact'] as $item) {
    if (is_string(stristr($item['Name'], $string))) {
      $id = $item['ContactID'];
      $matches[$id] = check_plain($item['Name']);
    }
  }

  drupal_json($matches);
}

/**
 * Xero Autocomplete Invoices page callback
 * @param $string the string to search
 */
function xero_autocomplete_invoices($string = '') {
  $invoices = xero_get_cache('Invoices');
  $matches = array();

  foreach ($invoices['Invoice'] as $item) {
    if (is_string(stristr($item['InvoiceNumber'], $string))) {
      $id = $item['InvoiceNumber'];
      $matches[$id] = check_plain($item['InvoiceNumber']);
    }
  }

  drupal_json($matches);
}
